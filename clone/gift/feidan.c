// feidan.c ���ӷɵ�

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIR "���ӷɵ�" NOR, ({ "nucleus bomb" }));
	set_weight(100);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "���Ǹ߿Ƽ���Ʒ����" RED "Ѫ����" NOR "���°汾��\n");
		set("value", 50000);
		set("no_sell", 1);
		set("unit", "ö");
	}
}

void init()
{
	add_action("do_launch", "launch");
	add_action("do_aim", "aim");
}

int do_launch(string arg)
{
	object me;
	object ob;
	string user;

	me = this_player();

	if (me->is_busy())
		return notify_fail("ʲô���鶼����æ������˵��\n");

	if (me->is_fighting())
		return notify_fail("������ٿ�����Щ����ɣ�\n");

	if (! arg || ! id(arg))
		return notify_fail("��Ҫ����ʲô��\n");

	if (! stringp(user = query_temp("aim")))
		return notify_fail("������׼(aim)���ٷ��䣡\n");

	if (! objectp(ob = find_player(user)) ||
	    ! me->visible(ob))
		return notify_fail("��Ҫը��������ں��������ϡ�\n");

	message_vision(HIM "$N�ͳ�һ��" + name() + HIM "������"
		       "�������5... 4... 3... 2... 1...��˵��һ�����أ�\n"
		       "�������䡱��һ����" + name() + HIM "�ڿն�ȥ��"NOR"\n", me);

	if (ob->query("env/no_idle"))
	{
		message_vision(HIG "ͻȻ��մ���һ�����˵�����...\n" +
			       "һ��" + name() + HIG "��Х���£�$N" + HIG
			       "�Ͻ�������һ�������գ�ֻ��һ������ô��"
			       "�������ѡ�"NOR"\n", ob);
		tell_object(me, "���" + name() + "û�����жԷ����ٽ�������\n");
		destruct(this_object());
		return 1;
	}

	message_vision(HIC "ͻȻ��մ���һ�����˵�����...\n" +
		       "���䡱��һ����$N" HIC "��ը�û�����С�̣�"
		       "һ�仰��˵������..."NOR"\n", ob);

	if (wizardp(ob))
		message_vision(HIM "$N" HIM "��æ��ȼһ�ŷ�ֽ������"
		       "ֱ��߶����̫���Ͼ�������...��"NOR"\n", ob);
	else
	{
		message_vision(HIG "$N" HIG "һ���޹��ı��飬��ԩ������"NOR"\n", ob);
		if (! ob->ban_say(1))
			CHANNEL_D->do_channel(this_object(), "rumor",
					      "��˵" + ob->name(1) +
					      "������ӷɵ�Ϯ�������ھ���ʧ����");
		ob->ban_say_until(10 * 60, "�����ڱ�ը��ͷ���ۻ���˵������");
		log_file("static/feidan", sprintf("%s��%s��%sʹ���˺��ӷɵ��ɹ���\n",ctime(time()),me->query("id"),ob->query("id")));
	}

	destruct(this_object());
	return 1;
}

int do_aim(string arg)
{
	object me;
	object ob;
	string my_id;

	if (arg && sscanf(arg, "%s with %s", arg, my_id) == 2 && ! id(my_id))
		return notify_fail("����û��(" + my_id + ")����������\n");

	if ((arg == "none" || arg == "cancel") && query_temp("aim"))
	{
		delete_temp("aim");
		write("����ȡ���ɵ���׼��\n");
		return 1;
	}

	me = this_player();

	if (! arg || ! objectp(ob = find_player(arg)) ||
	    ! me->visible(ob))
		return notify_fail("��Ҫ��׼�ĸ���ң�\n");

	if (me->is_busy())
		return notify_fail("ʲô���鶼����æ������˵��\n");

	if (me->is_fighting())
		return notify_fail("������ٿ�����Щ����ɣ�\n");

	if (me->ban_say())
		return notify_fail("������˵��������...����Ҳû�����䡣\n");

	tell_object(me, HIY "���ͳ�һ��" + name() + HIY "�������飬�����顣"NOR"\n", me);
	if (!random(10))
		message("vision", HIR "���۲����ǡ��������棬" + ob->name(1) +
			  HIR "�Ѿ�������" + name() +
			  HIR "��׼�ˡ�"NOR"\n", ob);
	log_file("static/feidan", sprintf("%s��%s��%sʹ���˺��ӷɵ���׼��\n",ctime(time()),me->query("id"),ob->query("id")));
	set_temp("aim", ob->query("id"));
	me->start_busy(5);

	return 1;
}

string long()
{
	object ob;
	string msg;

	msg = query("long");
	if (query_temp("aim") &&
	    objectp(ob = find_player(query_temp("aim"))))
	{
		msg += "������ö�ɵ�����׼��" + ob->name(1) +
		       "����������(launch)��\n";
	} else
		msg += "������ö�ɵ�������׼��״̬��"
		       "������ʱ��׼(aim)��\n";
	return msg;
}
