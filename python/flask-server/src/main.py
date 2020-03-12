#!/bin/env python3
import os
from flask import Flask, flash, request, redirect, send_from_directory, url_for
from werkzeug.utils import secure_filename

FILES_PATH = '/usr/src/app/files'
app = Flask(__name__)
app.config['FILES_PATH'] = FILES_PATH

@app.route('/')
def hello_world():
    return 'Hello World!'

@app.route('/download/<filename>')
def download_file(filename):
    return send_from_directory(app.config['FILES_PATH'],
                               filename)

@app.route('/upload', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        # check if the post request has the file part
        if 'file' not in request.files:
            flash('No file part')
            return redirect(request.url)
        file = request.files['file']
        # if user does not select file, browser also
        # submit an empty part without filename
        if file.filename == '':
            flash('No selected file')
            return redirect(request.url)
        else:
            filename = secure_filename(file.filename)
            file.save(os.path.join(app.config['FILES_PATH'], filename))
            return 'File Uploaded successfully!'
    return '''
    <!doctype html>
    <title>Upload new File</title>
    <h1>Upload new File</h1>
    <form method=post enctype=multipart/form-data>
      <input type=file name=file>
      <input type=submit value=Upload>
    </form>
    '''

if __name__ == '__main__':
    app.secret_key = 'super secret key'
    app.run(host='0.0.0.0', debug=True)
