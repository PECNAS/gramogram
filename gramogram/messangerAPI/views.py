import json

from django.shortcuts import render
from django.http import HttpResponse
from django.views import View

from django.views.decorators.csrf import csrf_exempt

class TestAPIView(View):
	def get(self, request):
		return HttpResponse("GET")

	@csrf_exempt
	def post(self, request):
		data = json.loads(request.body)

		return HttpResponse(data)