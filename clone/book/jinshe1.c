// jinshe1.c 

inherit ITEM;
inherit F_UNIQUE;

#include <ansi.h>; 

void setup()
{}

void create()
{
	set_name(YEL"��������ܸ��"NOR"�ϲ�", ({ "jinshe book1","book1", }));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("material", "paper");
		set("long",
	"����һ���ñ�ֽд�ɵ��顣���飺��������ܸ����\n"
	"��Ƥ���ƣ������Ѿ�����ܾ��ˡ�\n", );
		set("skill", ([
			"name"	: "jinshe-jian",
			"exp_required":	1000,
			"jing_cost"   :	55,
			"difficulty"  :	38,
			"min_skill"   : 50,
			"max_skill"   : 119,
		]));
	}
}

