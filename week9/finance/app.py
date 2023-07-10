import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

    # Query database for user stocks
    stocks = db.execute("SELECT symbol, SUM(shares) AS shares FROM transactions WHERE id = ? GROUP BY symbol HAVING SUM(shares) > 0", session["user_id"])

    # Calculate total value of stocks
    total = cash
    value = 0
    for stock in stocks:
        stock["price"] = lookup(stock["symbol"])["price"]
        stock["total"] = stock["price"] * stock["shares"]
        stock["price"] = usd(stock["price"])
        total += stock["total"]

    # Redirect user to home page
    value = total - cash
    cash = usd(cash)
    total = usd(total)
    value = usd(value)
    username = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])[0]["username"]
    return render_template("index.html", stocks=stocks, cash=cash, total=total, username=username, value=value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        # Ensure shares was submitted
        elif not request.form.get("shares"):
            return apology("must provide shares", 400)

        # Lookup stock
        stock = lookup(request.form.get("symbol"))

        # Check if stock exists
        if not stock:
            return apology("stock does not exist", 400)

        # Check if shares is a positive integer
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("shares must be a positive integer", 400)

        # Check if shares is a positive integer
        if shares < 1:
            return apology("shares must be a positive integer", 400)

        # Calculate total cost
        cost = shares * stock["price"]

        # Query database for user cash
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        # Check if user has enough cash
        if cash < cost:
            return apology("not enough cash", 400)

        # Update user cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - cost, session["user_id"])

        # Insert transaction into database
        db.execute("INSERT INTO transactions (id, symbol, shares, price) VALUES (?, ?, ?, ?)",
                   session["user_id"],
                   stock["symbol"],
                   shares,
                   stock["price"])

        # Redirect user to home page
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Query database for user transactions
    transactions = db.execute("SELECT * FROM transactions WHERE id = ?", session["user_id"])

    # Redirect user to home page
    for transaction in transactions:
        transaction["price"] = usd(transaction["price"])
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        # Lookup stock
        stock = lookup(request.form.get("symbol"))

        # Check if stock exists
        if not stock:
            return apology("stock does not exist", 400)

        stock["price"] = usd(stock["price"])

        # Redirect user to quoted page
        return render_template("quoted.html", stock=stock)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password was confirmed
        elif not request.form.get("confirmation"):
            return apology("must confirm password", 400)

        # Ensure password and confirmation match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match", 400)

        res = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if len(res) != 0:
            return apology("username already exists", 400)

        # Insert user into database
        result = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                            request.form.get("username"),
                            generate_password_hash(request.form.get("password")))

        # Check if username already exists
        if not result:
            return apology("username already exists", 400)

        # Redirect user to home page
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

            # Ensure symbol was submitted
            if not request.form.get("symbol"):
                return apology("must provide symbol", 400)

            # Ensure shares was submitted
            elif not request.form.get("shares"):
                return apology("must provide shares", 400)

            # Lookup stock
            stock = lookup(request.form.get("symbol"))

            # Check if stock exists
            if not stock:
                return apology("stock does not exist", 400)

            # Check if shares is a positive integer
            try:
                shares = int(request.form.get("shares"))
            except ValueError:
                return apology("shares must be a positive integer", 400)

            # Check if shares is a positive integer
            if shares < 1:
                return apology("shares must be a positive integer", 400)

            # Query database for user stocks
            stocks = db.execute("SELECT symbol, SUM(shares) AS shares FROM transactions WHERE id = ? GROUP BY symbol HAVING SUM(shares) > 0", session["user_id"])

            # Check if user has enough shares
            for stock1 in stocks:
                if stock1["symbol"] == request.form.get("symbol"):
                    if stock1["shares"] < shares:
                        return apology("not enough shares", 400)

            # Calculate total cost
            cost = shares * stock["price"]

            # Query database for user cash
            cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

            # Update user cash
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash + cost, session["user_id"])

            # Insert transaction into database
            db.execute("INSERT INTO transactions (id, symbol, shares, price) VALUES (?, ?, ?, ?)",
                    session["user_id"],
                    stock["symbol"],
                    -shares,
                    stock["price"])

            # Redirect user to home page
            return redirect("/")
    else:
        # Query database for user stocks
        stocks = db.execute("SELECT symbol, SUM(shares) AS shares FROM transactions WHERE id = ? GROUP BY symbol HAVING SUM(shares) > 0", session["user_id"])
        return render_template("sell.html", stocks=stocks)


@app.route("/deposit", methods=["GET", "POST"])
@login_required
def deposit():
    """Deposit cash"""
    if request.method == "POST":

        # Ensure amount was submitted
        if not request.form.get("amount"):
            return apology("must provide amount", 400)

        # Check if amount is a positive integer
        try:
            amount = int(request.form.get("amount"))
        except ValueError:
            return apology("amount must be a positive integer", 400)

        # Check if amount is a positive integer
        if amount < 1:
            return apology("amount must be a positive integer", 400)

        # Query database for user cash
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        # Update user cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash + amount, session["user_id"])

        # Redirect user to home page
        return redirect("/")
    else:
        capital = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        capital = usd(capital)
        return render_template("deposit.html", capital=capital)