// shanshen.c ��ɽ��

inherit ITEM;

void create()
{
	set_name("��ɽ��", ({"laoshan shen", "shen"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ��մ��ɽ��ĳ�����ɽ����\n");
		set("value", 10000);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	this_player()->add("eff_qi", 200);
	message_vision("$N����һ����ɽ����ֻ���û���һ����������ð��������\n", me);
	destruct(this_object());
	return 1;
}
