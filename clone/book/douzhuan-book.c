// douzhuan-book.c ��ת����

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(CYN "��ת����" NOR, ({ "douzhuan book", "douzhuan", "book" }));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "��");
		set("no_sell", 1);
		set("long", "����һ��������Ľ�ݼҶ�ת���Ƶ��ؼ���\n");
		set("value", 1000);
		set("material", "paper");
		set("skill", ([
			"name":	 "douzhuan-xingyi",
			"exp_required": 100000,
			"jing_cost" :   50,
			"difficulty":   40,
			"max_skill":    179,
			"min_skill":    100
		]) );
	}
}
