// jinshe2.c 
inherit ITEM;
inherit F_UNIQUE;

#include <ansi.h>

void setup()
{}

void create()
{
	set_name(YEL"��������ܸ��"NOR"�в�", ({ "jinshe book2","book2", }));
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("material", "paper");
		set("long",
	"����һ���ñ�ֽд�ɵ��顣���飺��������ܸ����\n"
	"��Ƥ���ƣ������Ѿ�����ܾ��ˡ�\n", );
		set("skill", ([
			"name"	: "jinshe-zhui",
			"exp_required":	100000,
			"jing_cost"   :	40,
			"difficulty"  :	35,
			"max_skill"   : 119,
		]));
	}
}

