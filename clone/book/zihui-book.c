// zihui-book.c �ϻ��ķ�

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(MAG "�ϻ��ķ�" NOR, ({ "zihui book", "zihui", "book" }));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "��");
		set("no_sell", 1);
		set("long", "����һ��������Ľ�ݼ��ϻ��ķ����ؼ���\n");
		set("value", 1000);
		set("material", "paper");
		set("skill", ([
			"name":	 "zihui-xinfa",  // name of the skill
			"exp_required": 100000,	 // minimum combat experience required
							// to learn this skill.
			"jing_cost" :   50,
			"difficulty":   40,	     // the base int to learn this skill
							// modify is gin_cost's (difficulty - int)*5%
			"max_skill":    179,	    // the maximum level you can learn
			"min_skill":    100	     // the maximum level you can learn
							// from this object.
		]) );
	}
}
