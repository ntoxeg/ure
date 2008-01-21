/**
 * NMXmlExporter.cc
 *
 * Author: Rodrigo Barra
 * Copyright(c) 2004 Vettatech Technologies
 * All rights reserved.
 */
#include "NMXmlExporter.h"
#include "NMXmlDefinitions.h"

std::string NMXmlExporter::toXML(HandleEntry *subset){	
	HandleSet *exportable = findExportables(subset);

	return(toXML(exportable));
}

HandleSet *NMXmlExporter::findExportables(HandleEntry *seed){
	//Finds the subset.
	HandleSet *exportables = new HandleSet();
	HandleSet *internalLinks  = new HandleSet();
	HandleEntry *it = seed;
	while (it != NULL){
		exportables->add(it->handle);
		Atom *atom = TLB::getAtom(it->handle);
		findExportables(exportables, internalLinks, atom);
		it = it->next;
	}
	delete(seed);
	//Eliminates internalLinks.
	HandleSetIterator *internals = internalLinks->keys();
	while (internals->hasNext()){
		Handle h = internals->next();
		exportables->remove(h);
	}
	delete(internals);
	delete(internalLinks);
	return(exportables);
}

void NMXmlExporter::findExportables(HandleSet *exportables, HandleSet *internalLinks, Atom *atom){
	for (int i = 0; i < atom->getArity(); i++){
		Handle h = atom->getOutgoingSet()[i];
		exportables->add(h);
		
		Atom *newAtom = TLB::getAtom(h);
		if (ClassServer::isAssignableFrom(LINK, newAtom->getType())){
			internalLinks->add(h);
		}
		findExportables(exportables, internalLinks, newAtom);
	}
}


std::string NMXmlExporter::toXML(HandleSet *elements){
	bool typesUsed[NUMBER_OF_CLASSES];
	char aux[1<<16];
	std::string result;

	sprintf(aux,"<%s>\n", LIST_TOKEN);
	result += aux;
	
	memset(typesUsed, 0, sizeof(bool)*NUMBER_OF_CLASSES);
	HandleSetIterator *it = elements->keys();
	while (it->hasNext()){
		exportAtom(it->next(), typesUsed, result);
	}
	delete(it);
	sprintf(aux,"<%s>\n", TAG_DESCRIPTION_TOKEN);
	result += aux;
	for (int i = 0 ; i < NUMBER_OF_CLASSES; i++){
		if (typesUsed[i]){
			sprintf(aux, "<%s %s=\"%s\" %s=\"%s\" />\n", TAG_TOKEN, NAME_TOKEN, ClassServer::getTypeName(i), VALUE_TOKEN, ClassServer::getTypeName(i));
			result += aux;
		}
	}
	sprintf(aux,"</%s>\n", TAG_DESCRIPTION_TOKEN);
	result += aux;

	sprintf(aux,"</%s>\n", LIST_TOKEN);
	result += aux;

	delete(elements);
	return(result);
}


void NMXmlExporter::exportAtom(Handle atomHandle, bool typesUsed[], std::string& result, bool isInternal){
	//printf("Exporting %s\n", TLB::getAtom(atomHandle)->toString().c_str());
	Atom *atom = TLB::getAtom(atomHandle);
	char aux[1<<16];
	typesUsed[atom->getType()] = true;
	if (ClassServer::isAssignableFrom(NODE, atom->getType())){
		if (!isInternal){
			sprintf(aux,"<%s %s=\"%f\" %s=\"%f\" ", ClassServer::getTypeName(atom->getType()), STRENGTH_TOKEN, atom->getTruthValue().getMean(), CONFIDENCE_TOKEN,atom->getTruthValue().getConfidence());
			result += aux;
		}else{
			sprintf(aux,"<%s %s=\"%s\" ", ELEMENT_TOKEN, CLASS_TOKEN, ClassServer::getTypeName(atom->getType())); 
			result += aux;
		}
		sprintf(aux,"%s=\"%s\" />\n", NAME_TOKEN, ((Node *)atom)->getName().c_str());
		result += aux;
	}else{
		sprintf(aux,"<%s %s=\"%f\" %s=\"%f\" ", ClassServer::getTypeName(atom->getType()), STRENGTH_TOKEN, atom->getTruthValue().getMean(), CONFIDENCE_TOKEN, atom->getTruthValue().getConfidence());
		result += aux;
		sprintf(aux,">\n");
		result += aux;

		for (int i = 0; i < atom->getArity(); i++){
			exportAtom(atom->getOutgoingSet()[i], typesUsed, result, true);
		}
		sprintf(aux,"</%s>\n", ClassServer::getTypeName(atom->getType()));
		result += aux;
	}
	
}

