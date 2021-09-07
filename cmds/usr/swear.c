// swear.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object ob;
	object old;
	string msg;

	if (! stringp(arg) || arg != "cancel" && sscanf(arg, "with %s", arg) != 1)
		return notify_fail("��Ҫ��˭һͬ���壿\n");

	if (me->is_busy() || me->is_fighting())
		return notify_fail("�ú�æ����ͷ�����飡\n");

	ob = present(arg, environment(me));

	if (objectp(old = me->query_temp("pending/swear")) &&
	    (ob || arg == "cancel"))
	{
		if (old != ob)
		{
			write("������˺�" + old->name(1) + "�������ͷ��\n");
			if (environment(old) == environment(me))
				tell_object(old, me->name(1) + "�����˺���������ͷ��\n");
		} else
		if (old->query_temp("pending/answer/" + me->query("id"), 1))
			return notify_fail("���������˼���������أ������˼һ�û�д�Ӧ�㡣\n");

		me->delete_temp("pending/swear");
		old->delete_temp("pending/answer/" + me->query("id"));
		if (arg == "cancel")
			return 1;
	}

	if (! ob)
		return notify_fail("����û������ˡ�\n");

	if (me->query_temp("pending/answer/" + ob->query("id")) &&
	    ob->query_temp("pending/swear") == me)
		return notify_fail("�������������������أ��㾿����Ӧ���ǲ���Ӧ��\n");


	if (! ob->is_character())
	{
		message_vision("$N����$n�����������������...��"
			       "�ǽ�ݰɣ��������ˣ���...������"
			       "���ˡ�\n", me, ob);
		return 1;
	}

	if (ob == me)
	{
		message_vision("$NĿ����ͣ����۷�ֱ�����������дʡ�\n", me);
		return 1;
	}

	if (me->query("age") < 18)
	{
		write("Сë���ӵ�ʲô�ң�һ����ȥ��\n");
		return 1;
	}

	if (ob->query("age") < 18)
	{
		write(ob->name() + "����һ��Сë���ӣ����ʡʡ�ɣ����˼��ˡ�\n");
		return 1;
	}

	if (! ob->query("can_speak"))
	{
		message_vision("$N����$nɵЦ�Ĳ�ͣ����֪������ʲôа��\n", me, ob);
		return 1;
	}

	if (stringp(me->query("born_family")) &&
	    me->query("born_family") != "û��" &&
	    me->query("born_family") == ob->query("born_family"))
	{
		write("����˼���ͬ����ӣ���ݸ�ʲô��\n");
		return 1;
	}

	if (me->is_brother(ob))
	{
		write("���Ѿ����������ˣ��ƺ�û�б�Ҫ����һ�ΰɡ�\n");
		return 1;
	}

	if (mapp(me->query("brothers")) && sizeof(me->query("brothers")) > 12)
	{
		write("�������ֵ�Ҳ̫���ˣ������Լ�����ǲ�����ˡ�\n");
		return 1;
	}

	if (! living(ob))
	{
		write(ob->name() + "���ڻ��Բ��ѣ��޷�����������\n");
		return 1;
	}

	me->start_busy(1);

	switch (random(6))
	{
	case 0:
		msg = "$N��$n����˵������$R������һ����ʣ��β��ʹ˽��壿��\n";
		break;
	case 1:
		msg = "$N̾�������������֪�����٣�$nn��������Ե�����պβ���"
		      "�ݣ���\n";
		break;
	case 2:
		msg = "$N����$n��ϲ����ʤ���������յ���$R��ʵ���������ң�����"
		      "��ݿɺã���\n";
		break;
	case 3:
		msg = "$N����һ��������������ǧ���׵ã��������٣�$nn�����Һβ�"
		      "�ʹ˽�ݣ���\n";
		break;
	case 4:
		msg = "$N������$nn��������������Ϊ���չ��⣬�㿴�ɺã���\n";
		break;
	default:
		msg = "$N����$n���֣�֣�ص���������������������"
		      "����꣬�����ѵã������ݿɺã���\n";
		break;
	}

	msg = replace_string(msg, "$nn", ob->name(1));
	msg = replace_string(msg, "$R", RANK_D->query_respect(ob));
	message_vision(msg, me, ob);

	if (! userp(ob))
	{
		write("����" + ob->name() + "��¶��ɫ�������ǲ�����Ȥ��\n");
		return 1;
	}

	tell_object(ob, YEL + me->name(1) + "��������ݣ����Ӧ(right)���ǲ���Ӧ(refuse)��"NOR"\n");
	ob->set_temp("pending/answer/" + me->query("id") + "/right",
		     bind((: call_other, __FILE__, "do_right", ob, me :), ob));
	ob->set_temp("pending/answer/" + me->query("id") + "/refuse",
		     bind((: call_other, __FILE__, "do_refuse", ob, me :), ob));
	me->set_temp("pending/swear", ob);

	return 1;
}

int do_right(object me, object ob)
{
	string msg;

	if (! ob || environment(ob) != environment(me))
		return notify_fail("��ϧ�����˼��Ѿ���������ˡ�\n");

	if (! living(ob))
		return notify_fail("�˼�������������˵�Ļ����������˰ɡ�\n");

	if (ob->query_temp("pending/swear") != me)
		return notify_fail("�˼������Ѿ�������������ˡ�\n");

	ob->delete_temp("pending/swear");

	if (me->is_brother(ob))
	{
		write("���Ѿ����������ˣ��ƺ�û�б�Ҫ����һ�ΰɡ�\n");
		return 1;
	}

	if (mapp(me->query("brothers")) && sizeof(me->query("brothers")) > 12)
	{
		message_vision("$NΪ�ѵĶ�$n�����������Ҳ���...ֻ��...��\n",
			       me, ob);
		write("�������ֵ�Ҳ̫���ˣ������Լ�����ǲ�����ˡ�\n");
		return 1;
	}

	message_vision("$N����$n��������ͷ������" + RANK_D->query_self(me) +
		       "���д��⣡���ã����ã���\n�԰գ�����"
		       "������£�����Ϊ�㣬һ���ͷ���ģ���"
		       "��ǹ��⣬��ͬ���㡣\n��������ƴ�"
		       "���أ�����ͬ��ͬ��ͬ��������Ըͬ��ͬ"
		       "��ͬ��������\n", me, ob);

	// ��¼����
	me->set("brothers/" + ob->query("id"), ob->name(1));
	ob->set("brothers/" + me->query("id"), me->name(1));
	me->save();
	ob->save();

	switch (random(3))
	{
	case 0:
		msg = "��˵" + me->name(1) + "�Ѻ�" +
		      ob->name(1) + "��Ϊ���չ��⣬����������";
		break;
	case 1:
		msg = "��˵" + me->name(1) + "��" + ob->name(1) +
		      "һ����ʣ��Ѿ���Ϊ���չ��⡣";
		break;
	default:
		msg = "��˵" + me->name(1) + "��" + ob->name(1) +
		      "���壬Я�����߽�����";
		break;
	}
	CHANNEL_D->do_channel(this_object(), "rumor", msg);
	return 1;
}

int do_refuse(object me, object ob)
{
	string msg;

	if (! ob || environment(ob) != environment(me))
		return notify_fail("��ϧ�����˼��Ѿ���������ˡ�\n");

	if (! living(ob))
		return notify_fail("�˼�������������˵�Ļ����������˰ɡ�\n");

	if (ob->query_temp("pending/swear") != me)
		return notify_fail("�˼������Ѿ�������������ˡ�\n");

	ob->delete_temp("pending/swear");

	switch (random(6))
	{
	case 0:
		msg = "$N�ٺٸ�Ц�˼�����������ɤ�ӣ���$n����"
		      "���������Ҹ��ʣ���\n";
		break;
	case 1:
		msg = "$Nһ��ü����$n��������... ���ƺ���̫��"
		      "�ɣ����Ǹ�����˵�ɣ���\n";
		break;
	case 2:
		msg = "$N������ɫ��������$nn�����������������"
		      "��ֻ��... ֻ��... ������˵Ҳ�ա���\n";
		break;
	case 3:
		msg = "$N̾��һ����������$nn����ֻ�Ǿ��ý���ʱ"
		      "����Щ������̸�����²�̫�ã���̫�ð�����\n";
		break;
	case 4:
		msg = "$N����һ������Ȼ���������ұ��ֲ��ϣ���"
		      "��������ҿ��������˰ɡ���\n";
		break;
	default:
		msg = "$N����$n��ֻ�ǹ����Ҷ������������ǲ�"
		      "�����$n��ݡ�\n";
		break;
	}

	msg = replace_string(msg, "$nn", ob->name(1));
	message_vision(msg, me, ob);
	tell_object(ob, "�����˼Ҷ���ûʲô��Ȥ��\n");

	return 1;
}

int help(object me)
{
   	write( @HELP
ָ���ʽ: swear cancel | with <someone>

��ĳ�˽��塣

see also��brothers
HELP );
   	return 1;
}
