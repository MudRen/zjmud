// tang.c

#include <ansi.h>

inherit ITEM;

void create()
{
	string *colors = ({ HIW, HIR, HIY, HIC, HIM, HIG });
	set_name(colors[random(sizeof(colors))] + "�ǹ�" NOR, ({ "sugar", "tang" }) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "����һ���ǣ�����ġ�"NOR"\n");
		set("value", 0);
		set("unit", "��");
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	message_vision("$N����һ��$n����������ǣ��ţ����𰡡�\n",
		       me, this_object());
	destruct(this_object());
	return 1;
}
