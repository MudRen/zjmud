// xiongdan1.c

inherit ITEM;

void create()
{
	set_name("�ܵ���", ({"xiongdan gan", "xiongdan", "gan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ���ܵ��ɡ�\n");
		set("value", 1000);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	me->set("eff_qi", me->query("max_qi"));
	message_vision("$N����һ���ܵ��ɣ����þ���ö��ˡ�\n", me);
	destruct(this_object());
	return 1;
}
