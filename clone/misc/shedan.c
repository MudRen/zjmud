// shedan.c

inherit ITEM;

void create()
{
	set_name("���ߵ�", ({"fushe dan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "ö");
		set("long", "����һö���ĸ��ߵ���\n");
		set("value", 500);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	message_vision("$Nһ�ھͰ�$n������ȥ��\n",
		       me, this_object());
	destruct(this_object());
	me->unconcious();
	return 1;
}

