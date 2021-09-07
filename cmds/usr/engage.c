// engage.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object witness;
	object ob;
	object old;
	string msg;

	seteuid(getuid());

	if (! arg)
		return notify_fail("��Ҫ��˭��飿\n");

	if (me->is_busy() || me->is_fighting())
		return notify_fail("�ú�æ����ͷ�����飡\n");

	ob = present(arg, environment(me));

	if (objectp(old = me->query_temp("pending/engage")) &&
	    (ob || arg == "cancel"))
	{
		if (old != ob)
		{
			write("���������" + old->name(1) + "������ͷ��\n");
			if (environment(old) == environment(me))
				tell_object(old, me->name(1) + "����������������ͷ��\n");
		} else
		if (old->query_temp("pending/answer/" + me->query("id"), 1))
			return notify_fail("���������˼�����ء�\n");

		me->delete_temp("pending/engage");
		old->delete_temp("pending/answer/" + me->query("id"));
		if (arg == "cancel")
			return 1;
	}

	if (! ob)
		return notify_fail("����û������ˡ�\n");

	if (me->query_temp("pending/answer/" + ob->query("id")) &&
	    ob->query_temp("pending/engage") == me)
		return notify_fail("����������������أ��㾿����Ӧ���ǲ���Ӧ��\n");


	if (! ob->is_character())
	{
		message_vision("$N�ճյ�����$n��������޸��Ұ�...�޸��Ұ�...�����Ƿ��ˡ�\n", me, ob);
		return 1;
	}

	if (ob == me)
	{
		message_vision("$NĿ����ͣ����۷�ֱ��\n", me);
		return 1;
	}

	if (me->query("gender") == "Ů��" && ob->query("gender") == "Ů��" ||
	    me->query("gender") != "Ů��" && ob->query("gender") != "Ů��")
	{
		write("�����" + ob->name(1) + "����������ƺ���̫���ʰɣ�\n");
		return 1;
	}

	if (me->query("class") == "bonze"&&( me->query("family/family_name") == "������"|| me->query("family/family_name") == "������"|| me->query("family/family_name") == "������"))
	{
		message_vision("$N��$n�ߺߵ�����ҲҪ��飬��ҲҪ��飡\n", me, ob);
		return 1;
	}

	if (ob->query("class") == "bonze"&&( ob->query("family/family_name") == "������"|| ob->query("family/family_name") == "������"|| ob->query("family/family_name") == "������"))
	{
		message_vision("$N��������Ķ�$n������컹�װɣ���Ҫ�����飡\n", me, ob);
		return 1;
	}

	if (! ob->query("can_speak"))
	{
		message_vision("$N����$nɵЦ��һ����̬��ģ����\n", me, ob);
		return 1;
	}

	if (me->query("couple/id") == ob->query("id"))
		return notify_fail("����Խ���ˮ��\n");

	if (me->query("couple"))
		return notify_fail("���Ҫ��ס�������ҳ��ɷ���һ�������ػ��߽������������\n");

	if (ob->query("couple"))
		return notify_fail("����ôҲ�õ��˼��������˵�ɣ�\n");

	if ((time()-me->query("divorce_time"))<86400*7 )
		return notify_fail("����ô��������»��ˣ�Ҳ̫ϲ������˰ɣ�\n");

	if ((time()-ob->query("divorce_time"))<86400*7 )
		return notify_fail("�Է����û��ã��������������ٻ飡\n");

	if (me->query("age") < 16)
	{
		message_vision("$N��$n������������Ҫ��쳤�������飡\n",me, ob);
		return 1;
	}

	if (ob->query("age") < 16)
	{
		message_vision("$N��$n������������Ҫ��쳤����Ҫ�����飡\n",me, ob);
		return 1;
	}

	me->start_busy(1);
	if (! objectp(witness = present("marriage witness", environment(me))))
	{
		if (me->query_temp("pending/engage_to") == ob->query("id"))
		{
			CHANNEL_D->do_channel(this_object(), "rumor",
				"��˵" + me->name(1) + "�¶����ģ�Ҫ��" +
				ob->name(1) + "˽������");
		} else
		{
			write("��������֤���˶�û�У�����˽�������Ҫ"
			      "��������������һ��������\n");
			me->set_temp("pending/engage_to", ob->query("id"));
			return 1;
		}
	} else
	{
		if (! living(witness))
			return notify_fail("û����" + witness->name() +
					   "����ſ�ڵ�����ô���㻹�ǵ�һ����ɡ�\n");

		if (witness->is_fighting())
			return notify_fail(witness->name() + "��������ܣ�" +
					   "�ﲻ�����æ��\n");

		return witness->do_witness(me, ob);
	}

	msg = (me->query("gender") == "Ů��") ? "$N���������Ķ�$n��������Ȣ���Ұɣ���\n"
					      : "$N֣�����µĶ�$n��������޸��Ұɣ���\n";

	message_vision(msg, me, ob);
	if (! living(ob))
	{
		write("Ȼ��" + ob->name() + "���Բ��ѣ��޷�����������\n");
		return 1;
	}

	if (! userp(ob))
	{
		write("����" + ob->name() + "��¶��ɫ������������������\n");
		return 1;
	}

	tell_object(ob, YEL + me->name(1) + "����������أ����Ӧ(right)���ǲ���Ӧ(refuse)��"NOR"\n");
	ob->set_temp("pending/answer/" + me->query("id") + "/right",
		     bind((: call_other, __FILE__, "do_right", ob, me :), ob));
	ob->set_temp("pending/answer/" + me->query("id") + "/refuse",
		     bind((: call_other, __FILE__, "do_refuse", ob, me :), ob));
	me->set_temp("pending/engage", ob);

	return 1;
}

int do_right(object me, object ob)
{
	object witness;

	if (! ob || environment(ob) != environment(me))
		return notify_fail("��ϧ�����˼��Ѿ���������ˡ�\n");

	if (! living(ob))
		return notify_fail("�˼�������������˵�Ļ����������˰ɡ�\n");

	if (ob->query_temp("pending/engage") != me)
		return notify_fail("�˼������Ѿ���������������ˡ�\n");

	ob->delete_temp("pending/engage");

	if (ob->query("couple"))
		return notify_fail("�˼��Ѿ�����ˣ��㻹�ǲ�Ҫȥ�˻�ˮ�ˣ�\n");

	if (me->query("couple"))
		return notify_fail("���Ҫ��ס�������ҳ��ɷ���һ�������ػ��߽������������\n");

	if (me->query("class") == "bonze"&&( me->query("family/family_name") == "������"|| me->query("family/family_name") == "������"|| me->query("family/family_name") == "������"))
		return notify_fail("���飿�����Ȼ��װɣ�\n");

	if (ob->query("class") == "bonze"&&( ob->query("family/family_name") == "������"|| ob->query("family/family_name") == "������"|| ob->query("family/family_name") == "������"))
		return notify_fail("���飿�����ȵ��˼һ��װɣ�\n");

	if ((time()-me->query("divorce_time"))<86400*7 )
		return notify_fail("����ô��������»��ˣ�Ҳ̫ϲ������˰ɣ�\n");

	if ((time()-ob->query("divorce_time"))<86400*7 )
		return notify_fail("�Է����û��ã��������������ٻ飡\n");

	if (witness = ob->query_temp("pending/marriage_witness"))
		return witness->do_right(me, ob);

	if (me->query("gender") == "Ů��")
	{
		switch (me->query("character"))
		{
		case "�ĺ�����":
			message_vision("$N΢΢��Ц�����ðɣ���"
				       "С����Ҿ�ͬ����ɡ�\n", me, ob);
			break;

		case "������":
			message_vision("$N�ߴ��Ķ�$n�����ð�...\n", me, ob);
			break;

		case "��������":
			message_vision("$N�������Ķ�$n�����ðɣ�\n", me, ob);
			break;

		default:
			message_vision("$N������$n������Ц������"
				       "���ð�������ϲ�����ˣ�\n", me, ob);
			break;
		}
	} else
	{
		switch (me->query("character"))
		{
		case "�ĺ�����":
			message_vision("$N΢΢��Ц�����ðɣ����Ǿ�������",
				       me, ob);
			break;

		case "������":
			message_vision("$NЦ���еĶ�$n�����ܺúܺã���...��...\n", me, ob);
			break;

		case "��������":
			message_vision("$N�����緢�Ķ�$n�����ã�\n", me, ob);
			break;

		default:
			message_vision("$N������$n������Ц������"
				       "���ð�������ϲ�����ˣ�\n", me, ob);
			break;
		}
	}

	me->set("couple/id", ob->query("id"));
	me->set("couple/name", ob->name(1));
	me->add("static/marry", 1);
	me->save();
	ob->set("couple/id", me->query("id"));
	ob->set("couple/name", me->name(1));
	ob->add("static/marry", 1);
	ob->save();
	CHANNEL_D->do_channel(this_object(), "rumor",
			      "��ϲ" + me->name(1) + "��" +
			      ob->name(1) + "˽������" +
			      (random(2) ? "�ս�����" : "����˫�ɡ�"));
	return 1;
}

int do_refuse(object me, object ob)
{
	object witness;

	if (! ob || environment(ob) != environment(me))
		return notify_fail("��ϧ�����˼��Ѿ���������ˡ�\n");

	if (! living(ob))
		return notify_fail("�˼�������������˵�Ļ����������˰ɡ�\n");

	if (ob->query_temp("pending/engage") != me)
		return notify_fail("�˼������Ѿ���������������ˡ�\n");

	ob->delete_temp("pending/engage");

	if (me->query("couple"))
	{
		message_vision("$N��ü�������Ѿ�����ˣ����Ҫ��"
			       "��ʵ�ڲ��ܴ�Ӧ��\n", me, ob);
		return 1;
	}

	if (witness = ob->query_temp("pending/marriage_witness"))
		return witness->do_refuse(me, ob);

	if (me->query("gender") == "Ů��")
	{
		switch (me->query("character"))
		{
		case "�ĺ�����":
			message_vision("$N��ü��Ŀ��$n����������"
				"����������⣿\n", me, ob);
			break;

		case "������":
			message_vision("$Nݸ��һЦ����$n������Ҫ�ˣ�"
				"����ô������̫���ʣ������Ժ�"
				"��˵�ɣ�\n", me, ob);
			break;

		case "��������":
			message_vision("$N�ɸɴ��Ķ�$n�����Ҳ�ͬ"
				"�⣬�����������İɣ�\n", me, ob);
			break;

		default:
			message_vision("$N������$n����Ц����Ҫ�ã�"
				"�ó����������ƽ���Ƹ�����"
				"��ǧ����������˵�ɣ�\n", me, ob);
			break;
		}
	} else
	{
		switch (me->query("character"))
		{
		case "�ĺ�����":
			message_vision("$N��ü��Ŀ��$n�����������"
				"������\n", me, ob);
			break;

		case "������":
			message_vision("$N����ת�˼�ת����$n�����α�"
				"�ż������¶������Ժ���˵��\n", me, ob);
			break;

		case "��������":
			message_vision("$Nҡҡͷ����$n�����������䲻"
				"���㣬�㻹����Ѱ�߾Ͱɣ�\n", me, ob);
			break;

		default:
			message_vision("$N������$n����Ц������������"
				"�αؽ���أ�������Ҳͦ�õ�ô��\n", me, ob);
			break;
		}
	}

	return 1;
}

int help(object me)
{
   	write( @HELP
ָ���ʽ: engage <someone>

��ĳ�������飬������Ǻ��л�����ã��������˰ɣ�

see also : divorce
HELP );
   	return 1;
}
