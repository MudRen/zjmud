//lhjiyu.c

#include <ansi.h>

inherit ITEM;
inherit F_FOOD;

void create()
{
	string name =HIY "�޺�����" NOR;
  	set_name(name, ({"luohan jiyu", "jiyu", "yu"}));
  	set_weight(300);
  	if (clonep())
    		set_default_object(__FILE__);
  	else 
	{
    		set("long", "һ�����˴��ѵ�"+name+"��\n");
    		set("unit", "��");
    		set("value", 1000);
    		set("food_remaining", 10);
    		set("food_supply", 30);
	}
}
