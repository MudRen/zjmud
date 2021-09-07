// suicide.c

#include <ansi.h>

inherit F_CLEAN_UP;

private int slow_suicide(object me);
private int halt_suicide(object me);
private void check_password(string passwd, object me, int forever);

int main(object me, string arg)
{
	object *inv;
	int i;
	//if (!wizardp(me))
	//	return notify_fail("�����У��ȴ����š�\n");
	if (me->is_busy())
		return notify_fail("����һ��������û��ɡ�\n");

	inv = deep_inventory(me);
	for (i = 0; i < sizeof(inv); i++)
	{
		if (! userp(inv[i]) && ! playerp(inv[i])) continue;
		return notify_fail("�����ϻ��и�������أ��벻��Ҳ��ѽ��\n");
	}

	if( me->query("marry"))
	{
		return notify_fail("�㻹�а����ڽ������ô�����ɱ��\n");
	}

	if( me->query("banghui"))
	{
		return notify_fail("�㻹��һ���ֵ��ڽ������ô�����ɱ��\n");
	}
	if( me->query("p_master/id"))
	{
		return notify_fail("�㻹��ʦ���ڽ������ô�����ɱ��\n");
	}
	//if( stringp(me->query("p_dizi")))
	if(sizeof(me->query("p_dizi"))>0)
	{
		return notify_fail("�㻹�е����ڽ������ô�����ɱ��\n");
	}
	if(me->query("inherit_to"))
	{
		return notify_fail("��Ȼ�Ѿ������²�����������ɱ��\n");
	}
	if(me->query("inherit_from"))
	{
		return notify_fail("��縺�Ŵ����²��²�����Ҫʹ����������ɱ��\n");
	}

	if( me->query("combat_exp") > 200000 )
	{
		return notify_fail("ɽ��ˮ������·������������һ�塣��λ" + RANK_D->query_respect(me) +"��Ҫ�������£��������侲һ����˵�ɣ���ʾ����ľ��鳬����Χ��\n");
	}

	if (! arg)
	{
		write(ZJOBLONG"��ѡ����ֱ��ɾ������ɱ��ʽ�������������Ͻ�������ɾ�������޷��ָ��������ؿ��ǡ�"ZJBR"��ȷ��Ҫ��ɱô��\n"
			ZJOBACTS2+ZJMENUF(3,3,8,30)+"ȷ��:suicide -f"ZJSEP"ȡ��:shake\n");
		return 1;
	}
	else if (arg == "-f") 
	{
		check_password("YES",me,1);
	}
	else
		return notify_fail("��Ҫ��ʲô��\n");
	return 1;
}

private void check_password(string passwd, object me, int forever)
{
	object link_ob;
	string old_pass;

	link_ob = me->query_temp("link_ob");
	old_pass = link_ob->query("ad_password");
	if (passwd!="YES")
	{
		write(HIR "������������Ȳ���ɱ�ˡ�"NOR"\n");
		return;
	}

	if (forever)
	{
		tell_object(me, HIR "\n�����Ҫ��ɱ�ˣ������ʮ�����ڲ���ڣ�����������ˡ�"NOR"\n");
		me->set_temp("suicide/time", time());
		me->set_temp("suicide/last", 0);
		me->set_temp("suicide/from", query_ip_number(me));
		me->start_busy(bind((: call_other, __FILE__, "slow_suicide", me :), me),
			       bind((: call_other, __FILE__, "halt_suicide", me :), me));
	}
}

int slow_suicide(object me)
{
	object link_ob;
	int t;

	if (! objectp(me) || previous_object() != me)
		return 0;

	t = time() - me->query_temp("suicide/time");
	if (t < me->query_temp("suicide/last"))
	{
		me->delete_temp("suicide/");
		return 0;
	}

	if (t < 30)
	{
		if (t - me->query_temp("suicide/last") < 5)
			return 1;

		tell_object(me, HIR"�㻹��" + chinese_number(30 - t) +
			    "������ϸ����("ZJURL("cmds:halt")+ ZJSIZE(20)+ HIC "ֹͣ��ɱ" NOR+HIR")��"NOR"\n");
		me->set_temp("suicide/last", t / 5 * 5);
		return 1;
	}

	link_ob = me->query_temp("link_ob");
	if (! link_ob || ! interactive(me)) return 0;

	log_file("static/suicide",
		 sprintf("%s %s commits a suicide from %s\n",
			log_time(), log_id(me),
			me->query_temp("suicide/from")));
	VIP_D->save_vdata(me);
	seteuid(getuid());
	write("\n�ðɣ�������:)��\n\n");
	if(me->query("combat_exp") > 0)
	{
		CHANNEL_D->do_channel(this_object(), "rumor",sprintf("%s��ɱ�ˣ��Ժ�����Ҳ������������ˡ�",me->name()));
	}
	tell_room(environment(me), me->name() +	"�������ǰ�������̣�������ʧ��...\n", ({me}));

	UPDATE_D->remove_user(me->query("id"));
	return 0;
}

int halt_suicide(object me)
{
	if (! objectp(me) || previous_object() != me)
		return 0;

	tell_object(me, HIG "�������Ѱ������ͷ��"NOR"\n");
	me->delete_temp("suicide");
	return 1;
}

int help (object me)
{
	write(@HELP
ָ���ʽ: suicide [-f]
 
�����Ϊĳ��ԭ���㲻�����, �����ѡ����ɱ.
��ɱ������:
 
suicide    : ����Ͷ̥
suicide -f : ��Զ�ĳ�ȥ�������, ϵͳ��Ҫ����
	     ����������ȷ�����.
 
������ѡ�� :)
 
HELP );
	return 1;
}
