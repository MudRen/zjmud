// cha.c �̲�

inherit ITEM;

void create()
{
	set_name("�̲�",({ "tea", "cha", "nai cha"}));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ��ŨŨ���̲裬ɢ�������˵�������\n");
		set("unit", "��");
		set("value", 300);
		set("remaining", 5);
		set("drink_supply", 60);
		set("only_do_effect", 1);
		set("can_drink", 1);
	}
	
	setup();
}

int do_effect(object me)
{
	if ((int)me->query("water") >= (int)me->max_water_capacity())
		return notify_fail("���Ѿ���̫���ˣ���Ҳ�಻��һ��ˮ�ˡ�\n");

	set("value", 0);
	me->add("water", (int)query("drink_supply"));

	me->receive_heal("qi", 50);
	add("remaining", -1);
	if (query("remaining"))
	{
		message_vision("$N�����̲裬�����˹��ˡ����˼��ڣ���"
			       "������������ˡ�\n", me);
	} else 
	{ 
		message_vision("$N�����˹��ˡ���ʣ�µ��̲�һ��"
			       "������ֻ����һ������ӿ��������\n", me);
		destruct(this_object());
	}
	return 1;
}

