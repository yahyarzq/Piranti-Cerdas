from flask import Flask, render_template, request
import sqlite3
import pickle
import pandas as pd
from sklearn.tree import DecisionTreeClassifier
from sklearn import tree

dataset_path = 'C:/Users/PC/Documents/Piranti Cerdas/Tugas 5/dataset/dataset.csv'
trained_model = 'C:/Users/PC/Documents/Piranti Cerdas/Tugas 5/web/dtc.sav'

app = Flask(__name__)

train = pd.read_csv(dataset_path)
from sklearn import preprocessing
le = preprocessing.LabelEncoder()
y_train = train['Label']
y_train = le.fit_transform(y_train)

def getdata(query):
    # Connecting to sqlite
    conn = sqlite3.connect('data.db')
    # Creating a cursor object using the cursor() method
    cursor = conn.cursor()
    sql = query
    cursor.execute(sql)
    rows = cursor.fetchall()
    if rows != None:
        label = rows[0][0]
    else:
        label = 'nodata'
    # Commit your changes in the database
    conn.commit()
    # Closing the connection
    conn.close()
    return label


@app.route('/')
def index():
    return render_template("http.html")


@app.route('/insert', methods=['POST'])
def insert():
    if request.method == 'POST':
        gx = request.form['gx']
        gy = request.form['gy']
        gz = request.form['gz']
        path = trained_model
        model = pickle.load(open(path, 'rb'))
        result = model.predict([[gx,gy,gz]])
        result = le.inverse_transform([result[0]])
        data = (gx, gy, gz, result[0])
        conn = sqlite3.connect('data.db')
        # Creating a cursor object using the cursor() method
        cursor = conn.cursor()
        sql = '''INSERT INTO data (gx,gy,gz,result) VALUES (?,?,?,?)'''
        cursor.execute(sql, data)
        # Commit your changes in the database
        conn.commit()
        # Closing the connection
        conn.close()
        return 'success'


@app.route('/reqlabel', methods=["GET", "POST"])
def reqlabel():
    if request.method == 'POST' and request.form['key'] == 'getdataLabel':
        query = '''SELECT result FROM data ORDER BY ID DESC LIMIT 1'''
        label = getdata(query)
        return label


@app.route('/reqx', methods=["GET", "POST"])
def reqx():
    if request.method == 'POST' and request.form['key'] == 'getdatax':
        query = '''SELECT gx FROM data ORDER BY ID DESC LIMIT 1'''
        label = getdata(query)
        return str(label)


@app.route('/reqy', methods=["GET", "POST"])
def reqy():
    if request.method == 'POST' and request.form['key'] == 'getdatay':
        query = '''SELECT gy FROM data ORDER BY ID DESC LIMIT 1'''
        label = getdata(query)
        return str(label)


@app.route('/reqz', methods=["GET", "POST"])
def reqz():
    if request.method == 'POST' and request.form['key'] == 'getdataz':
        query = '''SELECT gz FROM data ORDER BY ID DESC LIMIT 1'''
        label = getdata(query)
        return str(label)


if __name__ == "__main__":
    app.run(debug=True)
    app.run(host='0.0.0.0', port=80)
