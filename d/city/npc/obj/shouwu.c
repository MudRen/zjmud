// shouwu.c ������

inherit ITEM;

void create()
{
	set_name("������", ({"heshou wu", "wu"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�ó������εĺ����ڡ�\n");
		set("value", 10000);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	me->set("eff_qi", me->query("max_qi"));
	message_vision("$N����һ�ú����ڣ���ʱ�����ȫ������˻�����\n", me);
	destruct(this_object());
	return 1;
}
