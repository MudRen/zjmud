// mace.c

#include <ansi.h>
#include <weapon.h>

#define ADMIN   "???"
#define PARTY   "������"

inherit STAFF;

void create()
{
	set_name(HIG + PARTY + "Ȩ��" NOR, ({ "mace" }) );
	set_weight(30);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", HIG "һ����Ө��͸��Ȩ�ȣ�������ؤ���������Ŷ��\n"
				"����ϸһ�������ǣ�ԭ����ð�ƻ�����" + PARTY + "��Ȩ�ȡ�\n"
				"����ͨ��������˾�����(author)���������ǿ���(expell)���������ˡ�"NOR"\n");
		set("value", 1);
		set("no_sell", "����ʲô������\n");
		set("unit", "��");
		set("wield_msg", HIG "$N" HIG "����һ����Ө��͸��С����������"
				 "���ֵĺȵ����������ݼ�...��...��������"NOR"\n");
		set("unwield_msg", HIG "$N" HIG "�������İ�Ȩ���պá�"NOR"\n");
	}

	set("admin", ADMIN);
	init_staff(1);
	setup();
}

void init()
{
	if (this_player() == environment())
	{
		add_action("do_author", "author");
		add_action("do_expell", "expell");
	}

	add_action("do_owner", "owner");
}

int do_owner(string arg)
{
	object me;
	object ob;

	me = this_player();
	if (wiz_level(me) < wiz_level("(wizard)"))
		return notify_fail("������ (wizard) ���ϵ���ʦ������Ȩ��\n");

	if (! arg || ! objectp(ob = present(arg, environment(me))))
		return notify_fail("��Ҫ����" + name() + "����˭��\n");

	if (ob == me)
		return notify_fail("���Գ�����\n");

	if (! playerp(ob))
		return notify_fail("��ֻ�ܰ�Ȩ��������ҡ�\n");

	if (ob->query("party/party_name") &&
	    ob->query("party/party_name") != PARTY)
		return notify_fail(ob->name(1) + "�Ѿ������������ɣ������ʽ�����" + name() + "��\n");

	message_vision("$Nָ��ָ" + name() + "��������" + name() +
		       "�Ҿ���������" + ob->name(1) + "�ˡ�\n", me);
	ob->set("party/party_name", PARTY);
	set("admin", ob->query("id"));
	message_vision("$N��" + name() + "������$n��\n", me, ob);
	move(ob, 1);
	return 1;
}

int do_author(string arg)
{
	object me;
	object ob;

	me = this_player();
	if (me->query("id") != query("admin") && me->query("couple/id") != query("admin"))
		return notify_fail("�㲻��" + PARTY + "������������ˣ�û������ġ�\n");

	if (me->query("party/party_name") != PARTY)
		return notify_fail("���Լ�������" + PARTY + "���ˣ���ô�ձ��ˣ�\n");

	if (! arg || ! objectp(ob = present(arg, environment(me))))
		return notify_fail("��Ҫ����˭����" + PARTY + "��\n");

	if (! playerp(ob))
		return notify_fail("��ֻ��������Ҽ��뷢���\n");

	if (ob == me)
		return notify_fail("���Գ�����\n");

	if (ob->query("combat_exp") >= 50000)
		return notify_fail("���˾���̫�ߣ����˽���" + PARTY + "��\n");

	if (ob->query("party/party_name"))
	{
		if (ob->query("party/party_name") == PARTY)
			return notify_fail("�˼��Ѿ���" + PARTY + "�����ˡ�\n");

		return notify_fail("�˼��Ѿ�������������ˣ����ܼ������" + PARTY + "�ˡ�\n");
	}

	if (me->query_temp("author") == ob)
		return notify_fail("���Ѿ������˼��ˣ����Ǳ��˻�û�д�Ӧ��\n");

	if (! living(ob))
		return notify_fail("�������˼�û��������˵ʲô�ˡ�\n");

	message_vision("$N�߾�Ȩ�ȣ��ʵ�����" + ob->name(1) + "�����Ը������" +
		       PARTY + "����\n", me);
	ob->set_temp("pending/answer/" + me->query("id") + "/right",
		     (: call_other, __FILE__, "do_right", ob, me :));
	ob->set_temp("pending/answer/" + me->query("id") + "/refuse",
		     (: call_other, __FILE__, "do_refuse", ob, me :));
	me->set_temp("pending/author", ob);
	tell_object(ob, YEL + me->name(1) + "��������" + PARTY + "����ͬ�ⲻͬ��(right/refuse)��"NOR"\n");
	return 1;
}

int do_expell(string arg)
{
	object me;
	object ob;

	me = this_player();
	if (me->query("id") != query("admin") && me->query("couple/id") != query("admin"))
		return notify_fail("�㲻��" + PARTY + "������������ˣ�û������ġ�\n");

	if (! arg || ! objectp(ob = present(arg, environment(me))))
		return notify_fail("��Ҫ����˭����" + PARTY + "��\n");

	if (! playerp(ob))
		return notify_fail("��ֻ��������Ҽ��뷢���\n");

	if (ob == me)
		return notify_fail("���Գ�����\n");

	if (ob->query("party/party_name") != PARTY)
		return notify_fail("�˼Ҳ�����" + PARTY + "���ˣ��������㡣\n");

	message_vision("$N����һ�����ȵ�����" + ob->name(1) +
		       "�����ŷ���棬���ո��������ɣ���\n", me);
	ob->delete("party");

	CHANNEL_D->do_channel(this_object(), "rumor",
			      "��˵" + ob->name(1) + "��" + me->name(1) +
			      "������" + PARTY + "�ˡ�");
	return 1;
}

int do_right(object me, object ob)
{
	if (! ob || environment(ob) != environment(me))
		return notify_fail("��ϧ�����˼��Ѿ���������ˡ�\n");

	if (! living(ob))
		return notify_fail("�˼�������������˵�Ļ����������˰ɡ�\n");

	if (ob->query_temp("pending/author") != me)
		return notify_fail("�˼������Ѿ������������ˡ�\n");

	ob->delete_temp("pending/author");

	message_vision("$Nƴ����ͷ����С������һ����æ�������ã��ã��ã���\n", me);

	me->set("party/party_name", PARTY);
	CHANNEL_D->do_channel(this_object(), "rumor",
			      "��˵" + ob->name(1) + "��" + me->name(1) +
			      "����" + PARTY + "��");
	return 1;
}

int do_refuse(object me, object ob)
{
	if (! ob || environment(ob) != environment(me))
		return notify_fail("��ϧ�����˼��Ѿ���������ˡ�\n");

	if (! living(ob))
		return notify_fail("�˼�������������˵�Ļ����������˰ɡ�\n");

	if (ob->query_temp("pending/author") != me)
		return notify_fail("�˼������Ѿ������������ˡ�\n");

	ob->delete_temp("pending/author");
	message_vision("$Nһ�Ű�$n�߿����ȵ���������һ����ȥ����\n",
		       me, ob);
	tell_object(ob, "�����˼Ҷ����" + PARTY + "ûʲô��Ȥ��\n");

	return 1;
}

int query_autoload() { return query("admin"); }

void autoload(string para) { set("admin", para); }
