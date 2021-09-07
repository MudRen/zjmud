// letter.c
// ʦ������

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("ʦ���ż�", ({ "letter", "quest letter" }));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "��");
		set("long", "����һ��ʦ���������ױ��š�\n");
		set("value", 0);
	}
	setup();
}

void init()
{
	// ����
	add_action("do_accept", "accept");

	// �ܾ�
	add_action("do_refuse", "refuse");
}

// �鿴ʱ��ʾ������ʾ
string long()
{
	string msg;
	mapping quest;
	object me;

	//msg = query("long");
	msg = "�㷭���ż㷴�棬����ʦ�����л�˵��\n";
	if (! mapp(quest = query("quest")))
		return msg;

	me = this_player();
	if (me->query("id") != query("quester"))
		return msg;

	// call_out ��һ����׼ʱ����������Ҫ��ֹ����
	// ����һ�롱���������
	if (time() > query("dest_time"))
		return msg;

	//msg += "����д�ţ�\n";

	// Ϊ�������͵������ṩ��չ���
	switch (quest["type"])
	{
	case "kill" :
		// Ѱ�� master ̫���鷳����������͸��ݱ��˵��ƶ�
		// �ж���Ϣ
		msg += "\n�����͵���" + me->name() + "��";
		if (me->is_good())
		{
			msg += ("���Ŷ���" HIR + quest["name"] + NOR "��"+ quest["id"] +"����ҽ��ᣬ�޶�������������" HIR +
				quest["place"] + NOR "��û�����Ǵ��"
				"���Ὣ����ȥ������Ը�⣬����ҳ���"
				"�޷������������" HIR + 
				CHINESE_D->chinese_monthday(quest["limit"]) +
				NOR "֮ǰ��ɡ������ɽ�������ɡ�" +
				quest["master_name"] + "��" + 
				CHINESE_D->chinese_monthday(quest["time"]) + 
				"����\n");
		} else
		if (me->is_bad())
		{
			msg += ("������ν����" HIR + quest["name"] + NOR "��"+ quest["id"] +"���Ŵκ��������ԣ���������" HIR +
				quest["place"] + NOR "��û�����Ǵ��"
				"���Ὣ����ȥ������Ը�⣬����ҳ���"
				"�޷������������" HIR + 
				CHINESE_D->chinese_monthday(quest["limit"]) +
				NOR "֮ǰ��ɡ������ɽ�������ɡ�" +
				quest["master_name"] + "��" + 
				CHINESE_D->chinese_monthday(quest["time"]) + 
				"����\n");
		} else {
			msg += ("������ʿ" HIR + quest["name"] + NOR "��"+ quest["id"] +"����Ϊ�������ᣬ���Ž�������" HIR +
				quest["place"] + NOR "��û�����Ǵ��"
				"���Ὣ����ȥ������Ը�⣬����ҳ���"
				"�޷������������" HIR + 
				CHINESE_D->chinese_monthday(quest["limit"]) +
				NOR "֮ǰ��ɡ������ɽ�������ɡ�" +
				quest["master_name"] + "��" + 
				CHINESE_D->chinese_monthday(quest["time"]) + 
				"����\n");
		}
		break; 
	}
	// �������ܾ��Ļ������� refuse������� 30 ��Ҳû��ϵ
	msg += HIC "�����Ը����ܴ���������" HIW + 
	       chinese_number(query("dest_time") - time()) + 
	       HIC "��֮�ڣ�\n"ZJURL("cmds:accept quest")ZJSIZE(20)"ȷ��"NOR"����"ZJURL("cmds:refuse quest")ZJSIZE(20)"�ܾ�"NOR"\n";
	return msg;
}
string long2(object me)
{
	string msg;
	mapping quest;

	msg = "�㷭���ż㷴�棬����ʦ�����л�˵��\n";
	if (! mapp(quest = query("quest"))||!me)
		return msg;

	if (me->query("id") != query("quester"))
		return msg;

	// call_out ��һ����׼ʱ����������Ҫ��ֹ����
	// ����һ�롱���������
	if (time() > query("dest_time"))
		return msg;


	// Ϊ�������͵������ṩ��չ���
	switch (quest["type"])
	{
	case "kill" :
		// Ѱ�� master ̫���鷳����������͸��ݱ��˵��ƶ�
		// �ж���Ϣ
		msg += "\n�����͵���" + me->name() + "��";
		if (me->is_good())
		{
			msg += ("���Ŷ���" HIR + quest["name"] + NOR "��"+ quest["id"] +"����ҽ��ᣬ�޶�������������" HIR +
				quest["place"] + NOR "��û�����Ǵ��"
				"���Ὣ����ȥ������Ը�⣬����ҳ���"
				"�޷������������" HIR + 
				CHINESE_D->chinese_monthday(quest["limit"]) +
				NOR "֮ǰ��ɡ������ɽ�������ɡ�" +
				quest["master_name"] + "��" + 
				CHINESE_D->chinese_monthday(quest["time"]) + 
				"����\n");
		} else
		if (me->is_bad())
		{
			msg += ("������ν����" HIR + quest["name"] + NOR "��"+ quest["id"] +"���Ŵκ��������ԣ���������" HIR +
				quest["place"] + NOR "��û�����Ǵ��"
				"���Ὣ����ȥ������Ը�⣬����ҳ���"
				"�޷������������" HIR + 
				CHINESE_D->chinese_monthday(quest["limit"]) +
				NOR "֮ǰ��ɡ������ɽ�������ɡ�" +
				quest["master_name"] + "��" + 
				CHINESE_D->chinese_monthday(quest["time"]) + 
				"����\n");
		} else {
			msg += ("������ʿ" HIR + quest["name"] + NOR "��"+ quest["id"] +"����Ϊ�������ᣬ���Ž�������" HIR +
				quest["place"] + NOR "��û�����Ǵ��"
				"���Ὣ����ȥ������Ը�⣬����ҳ���"
				"�޷������������" HIR + 
				CHINESE_D->chinese_monthday(quest["limit"]) +
				NOR "֮ǰ��ɡ������ɽ�������ɡ�" +
				quest["master_name"] + "��" + 
				CHINESE_D->chinese_monthday(quest["time"]) + 
				"����\n");
		}
		break; 
	}
	// �������ܾ��Ļ������� refuse������� 30 ��Ҳû��ϵ
	msg += HIC "�����Ը����ܴ���������" HIW + 
	       chinese_number(query("dest_time") - time()) + 
	       HIC "��֮�ڣ�\n"ZJURL("cmds:accept quest")ZJSIZE(20)"ȷ��"NOR"����"ZJURL("cmds:refuse quest")ZJSIZE(20)"�ܾ�"NOR"\n";
	return msg;
}

private void eval_function(function fun) { evaluate(fun); }

// �Զ�ȡ��
void start_auto_cancel(object who, int timeout)
{
	tell_object(who,long2(who));
	call_out("refuse_quest", timeout, who);
}

// ��������
// ������һ������Ľ�����������һ������� npc
int do_accept(string arg)
{
	object head;
	object me;

	if (arg != "quest")
		return notify_fail("��Ҫ����ʲô��\n");

	if (query_temp("obsolete"))
		return 0;

	me = this_player();
	if (me->query("id") != query("quester"))
		return notify_fail("���ſɲ��Ǽĸ���ġ�\n");

	    if (!mapp(me->query("quest")))
	    {
		    if(QUEST_D->start_quest(me, query("quest")))
		    	message_sort(query("msg/accept"), me);

		    // Drop head
		    if (objectp(head = present("head", me)) && head->query("owner_id") == query("killed_id"))
		    {
			message_vision("$N�������е�" + head->name() +
				       "���ĵ�������Ȼ���ã�˳�־�������һ�ӡ�\n",
				      me);
			destruct(head);
		    } else
		    if (objectp(head = present("head", environment(me))) && head->query("owner_id") == query("killed_id"))
		    {
			message_vision("$N�������ϵ�" + head->name() +
				       "���ĵ�������Ȼ���ã�˳�־�������һ�ߡ�\n",
				      me);
			destruct(head);
		    }
	    } else
		    write("�㿴�˿��ţ��ƺ�ûɶ��Ҫ�ġ�\n");

	set_temp("obsolete", 1);
	call_out("dest_ob", 0, this_object());
	return 1;
}

// ��������
void dest_ob(object ob)
{
	destruct(ob);
}

// �ܾ�
int do_refuse(string arg)
{
	object me;

	if (arg != "quest")
		return notify_fail("��Ҫ�ܾ�ʲô��\n");

	if (query_temp("obsolete"))
		return 0;

	me = this_player();
	if (me->query("id") != query("quester"))
		return notify_fail("���ſɲ��Ǽĸ���ġ�\n");

	message_sort(query("msg/refuse"), me);

	set_temp("obsolete", 1);
	call_out("dest_ob", 0, this_object());
	return 1;
}

// CLASS_D("generate") + "/killed" ��ʱ���õ���������
void refuse_quest(object me)
{
	message_sort(query("msg/refuse"), me);

	remove_call_out("eval_function");
	call_out("dest_ob", 0, this_object());
}
