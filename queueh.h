#pragma once
//class Heron;

struct queue_element {
	void *who;
//	int harackter;
	queue_element *nextquh;
	queue_element(void* hwho=0,/*int character=0,*/ queue_element* next=0):who(hwho)/*,harackter(character)*/,nextquh(next)
	{}
};

bool quehappend(void* whus,/* int har,*/ queue_element**startque);
