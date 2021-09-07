#include <ansi.h>

inherit F_CLEAN_UP;

void global_destruct_player(object ob, int raw)
{
	object login_ob;

	if (objectp(ob) && ob->query_temp("temp_loaded"))
	{
		// ���Ӷ� login_ob ������
		if (objectp(login_ob = ob->query_temp("link_ob")))
		{
			if (raw) login_ob->save();
			destruct(login_ob);
		}
		
		if (raw) ob->save();
		destruct(ob);
	}
}

object global_find_player(string user)
{
	object ob;
	object login_ob;

	ob = find_player(user);
	if (! ob)
	{
		login_ob = new(LOGIN_OB);
		login_ob->set("id", user);
		ob = LOGIN_D->make_body(login_ob);
		if (! ob)
		{
			catch(destruct(login_ob));
			return 0;
		}

		evaluate(bind((: seteuid(getuid()) :), ob));

		if (! ob->restore())
		{
			catch(destruct(login_ob));
			catch(destruct(ob));
			return 0;
		}

		ob->set_temp("temp_loaded", 1);
		ob->set_temp("link_ob", login_ob);

		ob->start_call_out(bind((: call_other, __FILE__, 
				   "global_destruct_player", ob, 0 :),
				   ob), 0);

		login_ob->restore();
		login_ob->set_temp("body_ob", ob);
	}

	return ob;
}

int main(object me, string arg)
{
	object ob;

	if (! SECURITY_D->valid_grant(me, "(admin)"))
		return 0;

	if (!arg)
	{
		return notify_fail("ָ���ʽ��getuser <���ID>\n");
	}
	if (objectp(ob = global_find_player(arg)))
	{
		ob->move(environment(me));
		tell_object(me, HIM "���" + ob->name() + HIM "���˳�����"NOR"\n");
		tell_room(environment(me), HIM + ob->name() + HIM "ͻȻ����" +
			"������ǰ��"NOR"\n", ({ me, ob }));
		return 1;
	}
	else
	{
		return notify_fail("û�������һ�����������޷���ȡ��\n");
	}
}
int help(object me)
{
	write(@HELP
ָ���ʽ : getuser <ĳ��>

��ָ�������(��)��ĳ�����ߵ����ץ������ǰ��

������Ѿ����ߣ���ʹ��summon���

HELP );
	return 1;
}