#!/usr/bin/env python

from threading import Thread
import requests

def createUser(username):
	jsonCreateUser = {'username': username, 'password': username, 'name': username, 'mail': username + '@gmail.com', 'profilePicture': ''}
	requests.post('http://localhost:8080/user', json=jsonCreateUser)

if __name__ == "__main__":
	nThreads = 100000
	threads = []
	print "Test de stress iniciado"
	print "Creando " + str(nThreads) + " threads..."
	for i in range(0, nThreads):
		thread = Thread(target=createUser, args=(str(i), ))
		threads.append(thread)
	print "Iniciando threads..."
	for thread in threads:
		thread.start()
	print "Joining threads..."
	for thread in threads:
		thread.join()
	print "Test de stress finalizado"
