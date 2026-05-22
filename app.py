from flask import Flask, render_template, jsonify
import random

app = Flask(__name__)

movimentos = [
    "DIREITA",
    "ESQUERDA",
    "CIMA",
    "BAIXO",
    "PARADO"
]

@app.route('/')
def home():

    return render_template('index.html')

@app.route('/movimento')
def movimento():

    return jsonify({
        "movimento": random.choice(movimentos)
    })

app.run(debug=True)