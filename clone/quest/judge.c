// �������search.c

#include <ansi.h>
#include <quest.h>

inherit QUEST_OB;

#define QOB	     my["qob"]
#define NPC1	    my["npc1"]
#define NPC2	    my["npc2"]
#define NPC1_NAME       my["npc1_name"]
#define NPC2_NAME       my["npc2_name"]
#define NPC1_ID	 my["npc1_id"]
#define NPC2_ID	 my["npc2_id"]
#define PLACE	   my["place"]

string ask_1_for_2();
string ask_2_for_1();

// ������󴴽�
void create()
{
	setup();
}

// ����һ������
// ����һ����Ʒ����Ѱ�ң��Զ�������������������ص㣬����ɱ
// �˵�һ���˼��ɻ�ø���Ʒ��Ȼ�󽻸��ڶ�������ȡ������
void init_quest()
{
	string name;
	string place;
	object npc1, npc2;
	mapping my;

	// ������������ص�
	place = NPC_D->random_place(({ "����" }));

	// ���������������
	npc1 = new(CLASS_D("generate") + "/questnpc");
	npc2 = new(CLASS_D("generate") + "/questnpc");

	npc1->set_temp("quest_ob", this_object());
	npc2->set_temp("quest_ob", this_object());

	// �������������
	name = npc1->name(1) + "��" + npc2->name(1) + "����";
	set_name(name);

	// ��¼��Щ����ص����Ʒ��Ϣ
	my = query_entire_dbase();

	NPC1 = npc1;
	NPC2 = npc2;
	PLACE = place;
	NPC1_NAME = npc1->name();
	NPC2_NAME = npc2->name();
	NPC1_ID = npc1->query("id");
	NPC2_ID = npc2->query("id");

	// �������
	NPC_D->place_npc(npc1, 0, ({ place }));
	npc2->move(environment(npc1));
	npc1->delete("chat_chance");
	npc1->delete("chat_msg");
	npc2->delete("chat_chance");
	npc2->delete("chat_msg");

	// ���öԻ���Ϣ
	npc1->set("inquiry", ([
		NPC1_NAME : "�Ǿ��Ǳ������ˣ�",
		NPC1_ID   : "�Ǿ��Ǳ������ˣ�",
		NPC2_NAME : (: ask_1_for_2 :),
		NPC2_ID   : (: ask_1_for_2 :) ]));

	npc2->set("inquiry", ([
		NPC1_NAME : (: ask_2_for_1 :),
		NPC1_ID   : (: ask_2_for_1 :),
		NPC2_NAME : "�����������кι�ɣ�",
		NPC2_ID   : "�����������кι�ɣ�" ]));

	// �л�������״̬
	change_status(QUEST_READY);

	// ������������ʱ�䣺15����
	set("live_time", 900);

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

	// ��������
	::cancel_quest();
}

// ѯ��NPC1�й�NPC2������
string ask_1_for_2()
{
	mapping my = query_entire_dbase();

	if (! objectp(NPC2))
		return "�찡����...����ô���...��Ҳû����������";

	if (! environment(NPC2))
		return NPC2->name() + "��" + RANK_D->query_rude(NPC) +
		       "��֪���ﵽ����ȥ�ˡ�";

	switch (random(3))
	{
	case 0:
		return "��쵰����ֱ���ǲ���������";
	case 1:
		return "�������������ǵ���ʮ�˱��ӵ�ù������ʮ�ű��ӣ�";
	default:
		return "�Һ���û��������Ϊ����û��";
	}
}

// ѯ��NPC2�й�NPC1������
string ask_2_for_1()
{
	mapping my = query_entire_dbase();

	if (! objectp(NPC1))
		return "��...�ҿ�û���뺦��...���û�а���";

	if (! environment(NPC1))
		return "�����̵ģ�" + NPC2->name() + "���" +
		       RANK_D->query_rude(NPC) + "�����ˣ�";

	switch (random(3))
	{
	case 0:
		return "��Ҫ������������������Ҿ�������";
	case 1:
		return "������ң��������Ҷ��ġ�";
	default:
		return "����Ϊ�Լ��������ռ���ˣ��������찡�������׽���";
	}
}

// ѯ��NPC1��״��
string ask_npc1(object knower, object me)
{
	mapping my = query_entire_dbase();

	if (! objectp(NPC1))
		return CYN "�٣���˵" HIY + NPC1_NAME + NOR CYN
		       "���������ˣ��㿴�����������û�ô��ɣ�" NOR;

	return CYN "Ŷ������ѽ����Ҳ����ʶ����û���������ֺš�" NOR;
}

// ѯ��NPC2��״��
string ask_npc2(object knower, object me)
{
	mapping my = query_entire_dbase();

	if (! objectp(NPC2))
		return CYN "�٣���˵" HIY + NPC2_NAME + NOR CYN
		       "���˿��ˣ�Ƣ�����������³�ѽ��" NOR;

	return CYN "������û��ô��˵����������ª���Ű���" NOR;
}

// ѯ�ʵ���
string ask_shan(object knower, object me)
{
	if (me->query("weiwang") < 1000)
		call_out("do_whisper", 1, knower, me);

	return CYN "�������й��㶼����ʶ�������������˼ҿ�������"
		   "�е�\n����ѽ����ס̩ɽ��ר�ŵ��ڸ��־��ף���"
		   "��ƽ֮�¡�"NOR"\n";
}

// ֪ͨ���
void do_whisper(object knower, object me)
{
	if (! can_talk_with(knower, me))
		return;

	tell_object(me, WHT + knower->name() + WHT "���ĵĺ���"
		    "˵������ϧ��Ľ�������̫���ˣ��벻��������\n");
	message("vision", knower->name() + "��" + me->name() +
		"�Ķ������ĵ�˵��Щʲô��\n", environment(me), ({ me }));
}

// �������
string query_introduce(object knower)
{
	mapping my = query_entire_dbase();

	if (! objectp(NPC2))
	{
		remove_call_out("do_say");
		call_out("do_say", 1, knower);
	}

	return CYN "��˵" HIY + NPC1_NAME + NOR CYN "��" +
	       HIY + NPC2_NAME + NOR CYN "��" + PLACE +
	       CYN "�����˾��ף���֪��Ϊʲô��Ҫ��"
	       HIY "����" NOR CYN "�ھͺ��ˡ�" NOR;
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
	set_information(NPC1_ID, (: ask_npc1 :));
	set_information(NPC2_ID, (: ask_npc2 :));
	set_information("����", (: ask_shan :));
	set_information("shan zheng", (: ask_shan :));
}
