// yuping.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("��ͭ��", ({ "qingtong ding", "ding" }));
	set_weight(1500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "ֻ");
		set("long", "����һֻ�Ŵ�����ͭ����������ž����Ļ��ơ�\n");
		set("value", 10000);
		set("material", "copper");
	}
	setup();
}
