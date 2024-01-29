from django.urls import path
from .views import *

urlpatterns = [
	path("", TestAPIView.as_view())
]