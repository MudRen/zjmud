// jiuzhang.c

#include <ansi.h>
 
inherit ITEM;

void create()
{
	set_name(HIY "������������" NOR, ({ "jiuzhang", "shu" }));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ��������С���ӣ�����д��"
			    "�������������ĸ���׭С�֡�\n");
		set("value", 0);
		set("material", "paper");
		set("skill", ([
			"name":       "mathematics",
			"jing_cost":  100,
			"difficulty": 30,
			"max_skill":  149,
			"min_skill":  80
		]));
	}
}
