//shenshe.c
inherit ITEM;
void create()
{
	set_name("��·����", ({ "shen she", "snake"}));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ����ʶ·���������ߣ����԰����˴�����"
			    "��ɽ��(����home����)\n");
		set("unit", "��");
		set("value", 0);
	}
}

void init()
{
	add_action("do_home", "home");
}

int do_home()
{
	string dir;
	object me = this_player();
	object env;

	env = environment(me);

	if (env->short() != "��ɳĮ")
		return notify_fail("ʹ����·���߱���������ɳĮ��\n");

	if (! me->query("special/shenshe"))
		return notify_fail("�������Դ�����֪����ôʹ�á���·���ߡ���\n");

	message_vision("$N�ӻ����ͳ�����·���ߡ������ﲻ֪����Щʲô��\n"
		       "�ͼ�����·���ߡ�����о�ӣ�ҡͷ��β�ذ�$N������ɽ��ȥ������\n",me);
	me->move("/d/baituo/damen");
	return 1;
}
