from django.shortcuts import render
from django.http import HttpResponse
from django.views import View

class TestAPIView(View):
	def get(self, request):
		return HttpResponse("GET")

	def post(self, request):
		return HttpResponse("POST")