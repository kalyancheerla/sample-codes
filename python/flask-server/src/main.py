#!/bin/env python3
from flask import Flask, send_file
app = Flask(__name__)

@app.route('/')
def hello_world():
    return 'Hi! buddy'

@app.route('/download')
def download_file():
	path = "sample.xlsx"
	return send_file(path, as_attachment=True)

if __name__ == '__main__':
    app.run(host='0.0.0.0')
