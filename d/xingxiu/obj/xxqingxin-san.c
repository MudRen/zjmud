#include <ansi.h>

inherit ITEM;

void create()
{
   	set_name("����ɢ", ({"qingxin san", "san"}));
	set_weight(120);
   	if (clonep())
      		set_default_object(__FILE__);
   	else {
      		set("unit", "��");
      		set("value", 1000);
		set("only_do_effect", 1);
   	}
   	setup();
}

int do_effect(object me)
{
   	message_vision("$N����һ��" + name() + "��\n", me);
   	if ((int)me->query_condition("xx_poison") > 0)
      		me->clear("xx_poison");

   	destruct(this_object());
   	return 1;
}
