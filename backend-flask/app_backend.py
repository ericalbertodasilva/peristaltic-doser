# coding: utf-8

from app import app
from app.models import *

if __name__ == "__main__":
    import logging

    logging.basicConfig(filename='error.log', level=logging.DEBUG)
    app.run(debug=True)
