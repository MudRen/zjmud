// vote unchblk

#include <ansi.h>
#include <net/dns.h>

inherit F_CONDITION;

int clear_vote(object victim);

int vote(object me, object victim)
{
	string reason;  // vote for what?
	int vv;		// valid voter numbers
	int vc;	 // vote count;
	int df;
	string channel;
	string *juser, *jip, my_id, my_ip;
	string my_name, v_name;

	if (! interactive(me))
		return 0;

	if (victim->query_condition("vote_clear") &&
	    (reason = victim->query("vote/reason")) && reason != "unchblk")
  		return notify_fail("Ҫ�ѵ�ǰ�ı������Ժ�ſ������µĶ��顣\n");

	if (! victim->query("chblk_on"))
  		return notify_fail(victim->name(1) + "��Ƶ���Ѿ��Ǵ򿪵��ˡ�\n");
  
	if (! victim->query_condition("vote_clear"))
	{
		victim->set("vote/count", 0);
		reason = 0;
	}

	if (reason != "unchblk")
	{
		victim->set("vote/reason", "unchblk");
		victim->delete("vote/juror");
	}

	my_id = me->query("id");
	my_ip = query_ip_number(me);

	// dont allow me to vote twice for the same issue
	if (! arrayp(juser = victim->query("vote/juror/user")))
		juser = ({ });

	if (! arrayp(jip = victim->query("vote/juror/ip")))
		jip = ({ });
  
	if (member_array(my_ip, jip) != -1)
		return notify_fail("�����ڵ�IP��ַ�Ѿ�����Ͷ��Ʊ�ˡ�\n");
	else
	if (member_array(my_id, juser) == -1) 
	{
 		victim->set("vote/juror/user", juser + ({ my_id }));
		victim->set("vote/juror/ip", jip + ({ my_ip }));
	} else
	{
		me->add("vote/abuse", 1);
  		return notify_fail("һ��һƱ�����ñ��Ȩ��Ҫ�ܳͷ��ģ�\n");
	}

	vv = (int) ("/cmds/std/vote")->valid_voters(me) / 2;
	if (vv < 3) vv = 3;
	if (vv > 10) vv = 15;
	vc = victim->add("vote/count", 1);

	df = vv - vc;
  
	my_name = me->name();
	if (me == victim) v_name = "�Լ�"; else
			  v_name = victim->name(1);

	if (df >= 1)
	{
		message("vision", HIG "�����񹫾���" + my_name + "ͶƱ��"  + v_name + "��Ƶ��������" +
				  sprintf("%d", df) + "Ʊ��"NOR"\n", all_interactive());
    
		victim->apply_condition("vote_clear", 10);
		return 1;
	} else 
	{
  		if (me != victim)
			message("vision", HIG "�����񹫾���" + my_name + "ͶƱ��" + v_name + "��Ƶ����" +
					  v_name + "��Ƶ�������ˣ�"NOR"\n", all_interactive());
		else
			message("vision", HIG "�����񹫾���" + my_name + "ͶƱ���Լ���Ƶ����" +
					  my_name + "��Ƶ�������ˣ�"NOR"\n", all_interactive());
	}
	
	victim->clear_condition("vote_clear");
	victim->delete("vote/count");
	victim->delete("vote/reason");
	victim->delete("vote/juror");
	victim->delete("chblk_on");

	return 1;
}
