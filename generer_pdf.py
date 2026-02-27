#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Script de génération de PDFs pour E-Bank
Options 4 et 6 : Liste et statistiques des opérations
"""

import sys
from reportlab.lib.pagesizes import letter, A4
from reportlab.lib import colors
from reportlab.lib.units import inch
from reportlab.platypus import SimpleDocTemplate, Table, TableStyle, Paragraph, Spacer, PageBreak
from reportlab.lib.styles import getSampleStyleSheet, ParagraphStyle
from reportlab.lib.enums import TA_CENTER, TA_LEFT
from datetime import datetime

def generer_pdf_operations_compte(numero_compte, operations_data, output_filename):
    """
    Génère un PDF avec la liste des opérations d'un compte
    
    Args:
        numero_compte: Numéro du compte (ex: "CPT-001")
        operations_data: Liste de tuples (numero_op, date, montant, type)
        output_filename: Nom du fichier PDF de sortie
    """
    
    doc = SimpleDocTemplate(output_filename, pagesize=letter,
                           topMargin=0.75*inch, bottomMargin=0.75*inch)
    
    styles = getSampleStyleSheet()
    elements = []
    
    # Style personnalisé pour le titre
    title_style = ParagraphStyle(
        'CustomTitle',
        parent=styles['Heading1'],
        fontSize=18,
        textColor=colors.HexColor('#1E3A8A'),
        spaceAfter=30,
        alignment=TA_CENTER
    )
    
    # Titre
    title = Paragraph(f"<b>RELEVÉ DES OPÉRATIONS</b><br/>Compte : {numero_compte}", title_style)
    elements.append(title)
    
    # Date de génération
    date_gen = datetime.now().strftime("%d/%m/%Y à %H:%M")
    date_p = Paragraph(f"<i>Document généré le {date_gen}</i>", styles['Normal'])
    elements.append(date_p)
    elements.append(Spacer(1, 0.3*inch))
    
    if not operations_data:
        no_data = Paragraph("<b>Aucune opération enregistrée pour ce compte.</b>", styles['Normal'])
        elements.append(no_data)
    else:
        # En-têtes du tableau
        data = [['N° Opération', 'Date', 'Montant (FCFA)', 'Type']]
        
        # Données
        for op in operations_data:
            data.append(list(op))
        
        # Création du tableau
        table = Table(data, colWidths=[1.5*inch, 2*inch, 1.5*inch, 1.5*inch])
        
        # Style du tableau
        table.setStyle(TableStyle([
            # En-tête
            ('BACKGROUND', (0, 0), (-1, 0), colors.HexColor('#1E3A8A')),
            ('TEXTCOLOR', (0, 0), (-1, 0), colors.whitesmoke),
            ('ALIGN', (0, 0), (-1, -1), 'CENTER'),
            ('FONTNAME', (0, 0), (-1, 0), 'Helvetica-Bold'),
            ('FONTSIZE', (0, 0), (-1, 0), 12),
            ('BOTTOMPADDING', (0, 0), (-1, 0), 12),
            
            # Corps du tableau
            ('BACKGROUND', (0, 1), (-1, -1), colors.beige),
            ('GRID', (0, 0), (-1, -1), 1, colors.black),
            ('FONTNAME', (0, 1), (-1, -1), 'Helvetica'),
            ('FONTSIZE', (0, 1), (-1, -1), 10),
            ('ROWBACKGROUNDS', (0, 1), (-1, -1), [colors.white, colors.lightgrey]),
        ]))
        
        elements.append(table)
        elements.append(Spacer(1, 0.3*inch))
        
        # Résumé
        total_ops = len(operations_data)
        resume = Paragraph(f"<b>Total : {total_ops} opération(s)</b>", styles['Normal'])
        elements.append(resume)
    
    # Pied de page
    elements.append(Spacer(1, 0.5*inch))
    footer = Paragraph("<i>E-Bank - Système de Gestion Bancaire</i>", styles['Normal'])
    elements.append(footer)
    
    # Génération du PDF
    doc.build(elements)
    print(f"PDF généré : {output_filename}")


def generer_pdf_statistiques_compte(numero_compte, nb_total, nb_depots, nb_retraits, output_filename):
    """
    Génère un PDF avec les statistiques d'opérations d'un compte
    
    Args:
        numero_compte: Numéro du compte
        nb_total: Nombre total d'opérations
        nb_depots: Nombre de dépôts
        nb_retraits: Nombre de retraits
        output_filename: Nom du fichier PDF de sortie
    """
    
    doc = SimpleDocTemplate(output_filename, pagesize=letter,
                           topMargin=0.75*inch, bottomMargin=0.75*inch)
    
    styles = getSampleStyleSheet()
    elements = []
    
    # Style titre
    title_style = ParagraphStyle(
        'CustomTitle',
        parent=styles['Heading1'],
        fontSize=18,
        textColor=colors.HexColor('#1E3A8A'),
        spaceAfter=30,
        alignment=TA_CENTER
    )
    
    # Titre
    title = Paragraph(f"<b>STATISTIQUES DES OPÉRATIONS</b><br/>Compte : {numero_compte}", title_style)
    elements.append(title)
    
    # Date
    date_gen = datetime.now().strftime("%d/%m/%Y à %H:%M")
    date_p = Paragraph(f"<i>Document généré le {date_gen}</i>", styles['Normal'])
    elements.append(date_p)
    elements.append(Spacer(1, 0.5*inch))
    
    # Tableau des statistiques
    data = [
        ['Type d\'opération', 'Nombre'],
        ['DÉPÔTS', str(nb_depots)],
        ['RETRAITS', str(nb_retraits)],
        ['TOTAL', str(nb_total)]
    ]
    
    table = Table(data, colWidths=[3*inch, 2*inch])
    
    table.setStyle(TableStyle([
        # En-tête
        ('BACKGROUND', (0, 0), (-1, 0), colors.HexColor('#1E3A8A')),
        ('TEXTCOLOR', (0, 0), (-1, 0), colors.whitesmoke),
        ('ALIGN', (0, 0), (-1, -1), 'CENTER'),
        ('FONTNAME', (0, 0), (-1, 0), 'Helvetica-Bold'),
        ('FONTSIZE', (0, 0), (-1, 0), 14),
        ('BOTTOMPADDING', (0, 0), (-1, 0), 12),
        
        # Corps
        ('BACKGROUND', (0, 1), (-1, 2), colors.beige),
        ('BACKGROUND', (0, 3), (-1, 3), colors.HexColor('#FCD34D')),
        ('GRID', (0, 0), (-1, -1), 1, colors.black),
        ('FONTNAME', (0, 1), (-1, -1), 'Helvetica'),
        ('FONTSIZE', (0, 1), (-1, -1), 12),
        ('FONTNAME', (0, 3), (-1, 3), 'Helvetica-Bold'),
        ('FONTSIZE', (0, 3), (-1, 3), 14),
    ]))
    
    elements.append(table)
    elements.append(Spacer(1, 0.5*inch))
    
    # Note
    if nb_total == 0:
        note = Paragraph("<b>Aucune opération enregistrée pour ce compte.</b>", styles['Normal'])
    else:
        pct_depots = (nb_depots / nb_total * 100) if nb_total > 0 else 0
        pct_retraits = (nb_retraits / nb_total * 100) if nb_total > 0 else 0
        note = Paragraph(
            f"<b>Répartition :</b><br/>"
            f"• Dépôts : {pct_depots:.1f}%<br/>"
            f"• Retraits : {pct_retraits:.1f}%",
            styles['Normal']
        )
    
    elements.append(note)
    
    # Footer
    elements.append(Spacer(1, 0.5*inch))
    footer = Paragraph("<i>E-Bank - Système de Gestion Bancaire</i>", styles['Normal'])
    elements.append(footer)
    
    # Génération
    doc.build(elements)
    print(f"PDF généré : {output_filename}")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage:")
        print("  python generer_pdf.py operations <numero_compte> <output.pdf> [op1_data] [op2_data] ...")
        print("  python generer_pdf.py stats <numero_compte> <nb_total> <nb_depots> <nb_retraits> <output.pdf>")
        sys.exit(1)
    
    mode = sys.argv[1]
    
    if mode == "operations":
        # Format: python generer_pdf.py operations CPT-001 output.pdf "OP-001|01/01/2026|1000|DEPOT" "OP-002|..."
        numero_compte = sys.argv[2]
        output_file = sys.argv[3]
        
        operations = []
        for i in range(4, len(sys.argv)):
            parts = sys.argv[i].split('|')
            if len(parts) == 4:
                operations.append(tuple(parts))
        
        generer_pdf_operations_compte(numero_compte, operations, output_file)
    
    elif mode == "stats":
        # Format: python generer_pdf.py stats CPT-001 10 6 4 output.pdf
        numero_compte = sys.argv[2]
        nb_total = int(sys.argv[3])
        nb_depots = int(sys.argv[4])
        nb_retraits = int(sys.argv[5])
        output_file = sys.argv[6]
        
        generer_pdf_statistiques_compte(numero_compte, nb_total, nb_depots, nb_retraits, output_file)
    
    else:
        print(f"Mode inconnu : {mode}")
        sys.exit(1)
