
// �������capture.c

#include <ansi.h>
#include <quest.h>

inherit QUEST_OB;

#define NPC1	    my["npc1"]
#define NPC2	    my["npc2"]
#define NPC3	    my["npc3"]
#define NPC1_NAME       my["npc1_name"]
#define NPC2_NAME       my["npc2_name"]
#define NPC3_NAME       my["npc3_name"]
#define NPC1_ID	 my["npc1_id"]
#define NPC2_ID	 my["npc2_id"]
#define NPC3_ID	 my["npc3_id"]
#define PLACE1	  my["place1"]
#define PLACE2	  my["place2"]
#define PLACE3	  my["place3"]

string ask_2_for_1();
string ask_3_for_1();
string ask_3_for_2();
void npc_destructed();

// ������󴴽�
void create()
{
	setup();
}

// ����һ������
// �Զ���������׷�������Լ��������ʼ�ص㣬����ʼ��
// ɱ����һ�˿��Ի��һЩ�����Լ��ڶ��˵�ѶϢ��Ȼ����
// ɱ���ڶ��˻�ø���Ľ����͵����˵�ѶϢ�����ɱ����
// ���ˣ����������
void init_quest(string qob_name)
{
	string name;
	string place1, place2, place3;
	object npc1, npc2, npc3;
	mapping my;

	// ������������ص�
	place1 = NPC_D->random_place(({ "����", place1 }));
	place2 = NPC_D->random_place(({ "����", place2 }));
	place3 = NPC_D->random_place(({ "����", place3 }));

	// ���������������
	npc1 = new(CLASS_D("generate") + "/capturenpc1");
	npc2 = new(CLASS_D("generate") + "/capturenpc2");
	npc3 = new(CLASS_D("generate") + "/capturenpc3");

	npc1->set_temp("quest_ob", this_object());
	npc2->set_temp("quest_ob", this_object());
	npc3->set_temp("quest_ob", this_object());
	// ����������Ϣ��NPC���������Ժ��Զ��������
	npc3->set_temp("override/destruct", (: npc_destructed :));

	// �������������
	name = "׷ɱ" + npc1->name();
	set_name(name);

	// ��¼׷ɱ�����Լ��ص���Ϣ
	my = query_entire_dbase();

	NPC1 = npc1;
	NPC2 = npc2;
	NPC3 = npc3;
	PLACE1 = place1;
	PLACE2 = place2;
	PLACE3 = place3;
	NPC1_NAME = npc1->name();
	NPC2_NAME = npc2->name();
	NPC3_NAME = npc3->name();
	NPC1_ID = npc1->query("id");
	NPC2_ID = npc2->query("id");
	NPC3_ID = npc3->query("id");

	// ��������׷ɱ������һ����ֵģ������ڻ����Ӧ��Ѷ
	// Ϣ֮ǰɱ�����ǲ��޽���
	NPC_D->place_npc(npc1, 0, ({ place1 }));
	NPC_D->place_npc(npc2, 0, ({ place2 }));
	NPC_D->place_npc(npc3, 0, ({ place3 }));

	// ���öԻ���Ϣ
	npc1->set("inquiry", ([
		name      : "�ף�������£�����˼��������Ҳȥ���ơ�", // NPC1��װ��֪��
		NPC1_NAME : "����ʶ������ʶ��",
		NPC1_ID   : "����ʶ������ʶ��",
		NPC2_NAME : "�⡭���㻹���ұ����ʰɣ�����ҿɲ������",
		NPC2_ID   : "�⡭���㻹���ұ����ʰɣ�����ҿɲ������",
		NPC3_NAME : "��˵����˭ѽ����˵��������������û��˵����",
		NPC3_ID   : "��˵����˭ѽ����˵��������������û��˵����" ]));

	npc2->set("inquiry", ([
		name      : "��Ҫ׷ɱ����ȥ���������Ҹ������Ī�����",
		NPC1_NAME : (: ask_2_for_1 :),
		NPC1_ID   : (: ask_2_for_1 :),
		NPC2_NAME : "�������£��кι�ɣ�",
		NPC2_ID   : "�������£��кι�ɣ�",
		NPC3_NAME : "�⡭���㻹���ұ����ʰɣ�����ҿɲ������",
		NPC3_ID   : "�⡭���㻹���ұ����ʰɣ�����ҿɲ������" ]));

	npc3->set("inquiry", ([
		name      : "��˵���������ǲ�����������Ҫ׷ɱ��ȴ�����ң����ֲ���ʶ����",
		NPC1_NAME : (: ask_3_for_1 :),
		NPC1_ID   : (: ask_3_for_1 :),
		NPC2_NAME : "��������㵽����˵˭ѽ��",
		NPC2_ID   : "��������㵽����˵˭ѽ��",
		NPC3_NAME : "�������£��кι�ɣ�",
		NPC3_ID   : "�������£��кι�ɣ�" ]));

	// �л�������״̬
	change_status(QUEST_READY);

	// ������������ʱ�䣺50����
	set("live_time", 3000);

	// �Ǽ�ҥ����Ϣ
	register_information();
}

// ������ֹ
void cancel_quest()
{
	mapping my = query_entire_dbase();
	object env;

	if (! mapp(my))
		return;

	if (objectp(NPC1))
		destruct(NPC1);

	if (objectp(NPC2))
		destruct(NPC2);

	if (objectp(NPC3))
		destruct(NPC3);

	// ��������
	::cancel_quest();
}
// ����NPC����
void npc_destructed()
{
	call_out("cancel_quest", 0);
}
// ѯ��NPC2�й�NPC1������
string ask_2_for_1()
{
	mapping my = query_entire_dbase();

	if (! objectp(NPC1))
		return "�ţ��Ǽһﲻ�ǹ�����������������";

	switch (random(3))
	{
	case 0:
		return "��˵��������������û��˵����";
	case 1:
		return "�Ҳ�������ҿ��㻹���ұ������ʰɡ�";
	default:
		return "����ʶ������ʶ��";
	}
}

// ѯ��NPC3�й�NPC1������
string ask_3_for_1()
{
	mapping my = query_entire_dbase();

	if (! objectp(NPC1))
		return "�ţ��Ǽһﲻ�ǹ�����������������";

	switch (random(3))
	{
	case 0:
		return "��˵��������������û��˵����";
	case 1:
		return "�Ҳ�������ҿ��㻹���ұ������ʰɡ�";
	default:
		return "����ʶ������ʶ��";
	}
}

// ѯ��NPC1 - ��ʼ��׷ɱ����
string ask_npc1(object knower, object me)
{
	mapping my = query_entire_dbase();

	if (! objectp(NPC1))
		return CYN "�٣���˵" HIY + NPC1_NAME + NOR CYN "�Ѿ���"
		       "�˸����ˡ��٣�������ϵ�����û�������������Ҹ�˵"
		       "���˰ɡ�\n" + knower->name() + CYN "����˵������"
		       "���ִ�����Ϣ���ϴ������������ɵ���ı��Ȼ��������"
		       "ԭ���������ˣ���һ����ʲô" HIY + NPC2_NAME + NOR
		       + CYN "������ͽ��\n" + knower->name() + CYN "��˵"
		       "��������˵˵�������м����Դ����⼸���һ��Ȼ��һ"
		       "�������������ɣ��⻹�����ǻ�÷���" NOR;

	if (me->query("combat_exp") < NPC1->query("combat_exp") / 2)
	{
		remove_call_out("whisper_to1");
		call_out("whisper_to1", 0, knower, me);
	}

	me->set_temp("capture/" + NPC1_ID, 1);
	return CYN "Ŷ����˵������������Ѿ���" + PLACE1 + "����ȥ�ˣ���"
	       "���������С�������ޡ�\n" + knower->name() + CYN "����˵"
	       "�����������˾͵�ͼ��̫ƽ���α�ȥ����ô���鷳�أ���˵�Բ�"
	       "��" NOR;
}

// ѯ��NPC2 - �ڶ�����׷ɱ�Ķ���
string ask_npc2(object knower, object me)
{
	mapping my = query_entire_dbase();

	if (! objectp(NPC2) && objectp(NPC1))
		return CYN "��û��˵�����ף����ˣ�ǰ�����и���"
		       "����ˣ������е�����Ҫ�ҵ��ˡ�" NOR;

	if (objectp(NPC1))
		return CYN "���������������Ҵ�û��˵�����Ǻ�"
		       "�ˣ�" NOR;

	if (! objectp(NPC2))
		return CYN "��ղ�û����ҥ��ô����˵�Ǹ�" HIY +
		       NPC2_NAME + NOR CYN "����Ҳ���ˡ�������"
		       "����������������ǵ��³���\n" + knower->name()
		       + CYN "����˵�������������ִ�������Ϣ��"
		       "�����������ɵ���ı��ȻҲ������������һ"
		       "����" HIY + NPC3_NAME + NOR + CYN "����"
		       "��Ļ����ݡ�\n" + knower->name() + CYN
		       "�����������������������Щ�һﰡ��һ��"
		       "��һ�ݣ�" NOR;

	if (me->query("combat_exp") < NPC2->query("combat_exp") / 2)
	{
		remove_call_out("whisper_to2");
		call_out("whisper_to2", 0, knower, me);
	}

	me->set_temp("capture/" + NPC2_ID, 1);
	return CYN "��ѽѽ��������һ����̽��Ϣ�ġ���˵�Ǽһ���"
	       "���������Ѿ�����������\n" + knower->name() + CYN
	       "����˵��������ǰ���쵹����һ�����ڵ���Ъ�ţ���"
	       "֪��ô�ľ�̸����������˵�����Ƕ㵽" + PLACE2 +
	       "ȥ�ˡ�" NOR;
}

// ѯ��NPC3 - ����׷ɱ����
string ask_npc3(object knower, object me)
{
	mapping my = query_entire_dbase();
/*
	if (! objectp(NPC3) && objectp(NPC1))
	{
		remove_call_out("cancel_quest");
		call_out("cancel_quest", 2);
	}
		return CYN "��û��˵�����ף����ˣ�ǰ�����и���"
		       "����ˣ������е�����Ҫ�ҵ��ˡ�" NOR;

	if (! objectp(NPC3) && objectp(NPC2))
	{
		remove_call_out("cancel_quest");
		call_out("cancel_quest", 2);
	}
		return CYN "��û��˵�����ף����ˣ�ǰ�����и���"
		       "����ˣ������е�����Ҫ�ҵ��ˡ�" NOR;
*/
	if (objectp(NPC1) || objectp(NPC2))
		return CYN "���������������Ҵ�û��˵�����Ǻ�"
		       "�ˣ�" NOR;

	if (! objectp(NPC3))
		return CYN "���ˣ�ȫ�����ˡ�" HIY + NPC3_NAME +
		       NOR CYN "Ҳ���˸����ˡ������㣬����" HIY
		       + NPC1_NAME + NOR + CYN "��Ȼ����" HIY +
		       NPC2_NAME + NOR + CYN "���������ֵ�����"
		       "\n" + knower->name() + CYN "����˵����"
		       "��������˭�����ǰѸ��ǵĺͲ����ǵĶ���"
		       "���˰������¶��������Ѿ͸����ˡ�" NOR;

	if (me->query("combat_exp") < NPC3->query("combat_exp") / 2)
	{
		remove_call_out("whisper_to3");
		call_out("whisper_to3", 0, knower, me);
	}

	me->set_temp("capture/" + NPC3_ID, 1);
	return CYN "��˵��һ����Կ���ã��ȵ���ͬ��ȫ��������"
	       "������������\n" + knower->name() + CYN "����"
	       "˵������������������Ҳ���������������յ���Ϣ��"
	       "�Ѿ�ֱ��" + PLACE3 + "����ȥ�ˡ�\n" + knower->name()
	       + CYN "���һ�������ŵ�����˵�ɣ����ܹ���е�ù"
	       "��һ�졣������ù���һ��Ͳ���ʮ�塣" NOR;
}

void whisper_to1(object knower, object me)
{
	mapping my = query_entire_dbase();

	if (! can_talk_with(me, knower))
		return;

	message("vision", knower->name() + "���ĵ���" + me->name()
		+ "����˵��Щʲô��\n", environment(me), ({ me }));

	tell_object(me, WHT + knower->name() + WHT "���ĵĶ���˵��"
		     + RANK_D->query_respect(me) + "���ҿ���ͱ���"
		    "���ˮ�ˣ�" + NPC1_NAME + WHT "�������أ�"NOR"\n");
}

void whisper_to2(object knower, object me)
{
	mapping my = query_entire_dbase();

	if (! can_talk_with(me, knower))
		return;

	message("vision", knower->name() + "���ĵ���" + me->name()
		+ "����˵��Щʲô��\n", environment(me), ({ me }));

	tell_object(me, WHT + knower->name() + WHT "���ĵĶ���˵��"
		     + RANK_D->query_respect(me) + "���ҿ���ͱ���"
		    "���ˮ�ˣ�" + NPC2_NAME + WHT "�������أ�"NOR"\n");
}

void whisper_to3(object knower, object me)
{
	mapping my = query_entire_dbase();

	if (! can_talk_with(me, knower))
		return;

	message("vision", knower->name() + "���ĵ���" + me->name()
		+ "����˵��Щʲô��\n", environment(me), ({ me }));

	tell_object(me, WHT + knower->name() + WHT "���ĵĶ���˵��"
		     + RANK_D->query_respect(me) + "���ҿ���ͱ���"
		    "���ˮ�ˣ�" + NPC3_NAME + WHT "�������أ�"NOR"\n");
}

// �������
string query_introduce(object knower)
{
	mapping my = query_entire_dbase();

	if (objectp(NPC1))
		return CYN "��ѽѽ����˵" HIY + NPC1_NAME + NOR +
		       CYN "�Ǽһﲻ֪��ô��ģ���Ȼ�ѽ�����������"
		       "��ȫ�������ˣ��������֣�\n" + knower->name()
		       + CYN "����˵��������һ�����������ɱ�ų���"
		       "�ţ�ֻҪ���˼����������ϸ�ɱ���ۡ�" NOR;

	if (objectp(NPC2) && ! objectp(NPC1))
		return CYN "���յ���Ϣ�����ϴ��������������Ǽ���"
		       "����ı��Ȼ����" HIY + NPC1_NAME + NOR + CYN
		       "������һ������" HIY + NPC2_NAME + NOR + CYN
		       "���ڱ���ָʹ��\n" + knower->name() + CYN
		       "����˵��������" HIY + NPC1_NAME + NOR + CYN
		       "���³�Ҳ��ң�����ֻ�Ǹ����ף����ȴ��һ��"
		       "���˼Ҹ����ˡ�" NOR;

	if (objectp(NPC3) && ! objectp(NPC2) && ! objectp(NPC1))
		return CYN "�벻�����벻��������²¿����ϴ�������"
		       "�����ɵ���ı��˭��\n" + knower->name() + CYN
		       "�ٺ�һЦ��������������Ȳ���" HIY + NPC1_NAME
		       + NOR + CYN "��Ҳ����" HIY + NPC2_NAME + NOR +
		       CYN "������һ����" HIY + NPC3_NAME + NOR + CYN
		       "������Ļ��ȫȨ���ݣ�\n" + knower->name() +
		       CYN "����˵�����������������Ѿ��յ�����Ϣ��׼"
		       "��ȫ��׷����ȥ�ˡ�" NOR;

	if (! objectp(NPC3))
		return CYN "�ٺ٣������������ˣ�Ҳ����̫ƽ�ˡ�\n��"
		       "С������һ�����������㣬����" HIY + NPC1_NAME
		       + NOR + CYN "��Ȼ����" HIY + NPC2_NAME + NOR
		       + CYN "���������" HIY + NPC3_NAME + NOR + CYN
		       "��\n" + knower->name() + CYN "�ֽ��ŵ�������"
		       "����˭�����ǰѸ��ǵĺͲ����ǵĶ������˰�����"
		       "�¶��������Ѿ͸����ˡ�" NOR;
}

// �����Ϣ�ܹ���ɢ����
int can_rumor_by(object knower)
{
	// 20%�ļ��ʱ�ɢ��
	return (random(10) < 2);
}

// �ǼǸ��������Ϣ
void register_information()
{
	mapping my = query_entire_dbase();

	if (! clonep() || ! mapp(my))
		// �����������Բ��Ǽ�
		return;

	set_information(NPC1_NAME, (: ask_npc1 :));
	set_information(NPC2_NAME, (: ask_npc2 :));
	set_information(NPC3_NAME, (: ask_npc3 :));
	set_information(NPC1_ID, (: ask_npc1 :));
	set_information(NPC2_ID, (: ask_npc2 :));
	set_information(NPC3_ID, (: ask_npc3 :));
}
