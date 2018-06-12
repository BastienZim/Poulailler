from django.shortcuts import render
from django.http import HttpResponse

valeur_oeuf = 8
qte_grain = 9

# Create your views here.
def index(request):
    rep =HttpResponse()
    rep.write("<h1>Le site du Poulailler : Informations<h1/><hr />")
    rep.write("<p>Le nombre d'oeufs est de : ")
    rep.write(valeur_oeuf)
    rep.write(" oeufs</p>")
    rep.write("<p>La quantite de grain restant est de : ")
    rep.write(qte_grain)
    rep.write(" g </p>")
    rep.write("<p>La quantite d'eau restant est de : ")
    rep.write(qte_grain)
    rep.write(" ml </p>")
    return HttpResponse(rep)

