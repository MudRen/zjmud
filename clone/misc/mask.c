// mask.c
//

inherit ITEM;

void create()
{
	set_name("���", ({ "mian ju", "mask" }) );
	set_weight(3000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "���ƺ���һ������Ƥ�Ƴɵ���ߡ�\n");
		set("value", 10000);
	}
	setup();
}

void init()
{
	add_action("do_pretend", "pretend");
}

int do_pretend(string arg)
{
	object who;
	object me;
	string *mask;
	string pshort;

	if (! arg)
		return notify_fail("�����װ˭��\n");

	me = this_player();
	if (arg == "none" || arg == "cancel")
	{
		if (! query_temp("owner"))
			return notify_fail("�����ڲ�û��ʹ����ߡ�\n");

		me->delete_temp("apply/name");
		me->delete_temp("apply/short");
		me->delete_temp("apply/long");
		message_vision("$N������ȡ����һ����Ƥ��ߡ�\n", me);
		return 1;
	}

	if (me->query_skill("pretending", 1) < 100)
		return notify_fail("���������������ȥ�����ǲ���ʹ�á�\n");

	if (me->query("age") >= 60 &&
	    ! me->query("special_skill/youth"))
		return notify_fail("��̫���ˣ����԰����\n");

	if (! objectp(who = present(arg, environment(me))) || 
	    ! living(who))
		return notify_fail("�����װ˭��\n");

	if (wizardp(who))
		return notify_fail("���޷��ٰ���ʦ��\n");

	if (! who->query("can_speak"))
		return notify_fail("�ٰ�" + who->name() + "������̫���˵㡣\n");

	// ��Ϊ����short()��ʱ�������Է���״̬�����Բ�ֱ��
	// ����who->short()������ֱ�ӿ����ƶԷ���Ӧ��short()��
	// ���û�о͸��ƶԷ�����ʵshort()��
	if (sizeof(mask = who->query_temp("apply/short")))
		pshort = mask[sizeof(mask) - 1];
	else
		pshort = who->short(1);

	write("�㿪ʼ��װ" + who->name() + "��\n");
	me->set_temp("apply/name", ({ who->name() }));
	me->set_temp("apply/short", ({ pshort }));
	me->set_temp("apply/long", ({ who->long() }));
	set_temp("owner", me);
	return 1;
}

int move(mixed dest)
{
	object me;

	if (me = query_temp("owner"))
	{
		me->delete_temp("apply/name");
		me->delete_temp("apply/short");
		me->delete_temp("apply/long");
		delete_temp("owner");
	}

	return ::move(dest);
}


