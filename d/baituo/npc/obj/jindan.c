// more work needed to use this object to make poison

inherit ITEM;

void create()
{
	set_name("���ߵ�", ({"jin dan", "jin"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "ֻ");
		set("long", "����һֻ�ƲӲӵĽ��ߵ���\n");
		set("value", 200);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	message_vision("$Nһ��ͷ��������$n��\n", me, this_object());
	me->set_temp("die_reason", "����һö�ߵ����ж�����");
	me->die();
	destruct(this_object());
	return 1;
}
