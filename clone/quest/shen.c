// �������shen.c

#include <ansi.h>
#include <quest.h>

inherit QUEST_OB;

#define QOB	     my["qob"]
#define NPC_OB	  my["npc_ob"]
#define NPC_ID	  my["npc_id"]
#define NPC_NAME	my["npc_name"]
#define PLACE	   my["place"]
#define TYPE	    my["type"]
#define ZONE	    my["zone"]

void npc_destructed();

// ������󴴽�
void create()
{
	setup();
}

// ����һ������
// ɱһ���˼��ɻ����Ľ�����
void init_quest()
{
	string name;
	object qob;
	string place;
	object npc;
	mapping my;
	int type;

	// ������������ص�
	place = NPC_D->random_place(({ "����" }));

	// ���������������
	npc = new(CLASS_D("generate") + "/shennpc");
	npc->set_temp("quest_ob", this_object());

	// ����������Ϣ��NPC���������Ժ��Զ��������
	npc->set_temp("override/destruct", (: npc_destructed :));

	// �������������
	if (type = random(2))
	{
		name = "����" + npc->name();
		npc->set("shen_type", -1);
	} else
	{
		name = "����" + npc->name();
		npc->set("shen_type", 1);
	}
	set_name(name);

	// ��¼��Щ����ص����Ʒ��Ϣ
	my = query_entire_dbase();

	TYPE = type;
	NPC_OB = npc;
	PLACE = place;
	NPC_NAME = npc->name();
	NPC_ID   = npc->query("id");

	// �������
	NPC_D->place_npc(npc, 0, ({ place }));

	if (sscanf(file_name(environment(npc)), "/d/%s/%*s", ZONE) == 2)
	    ZONE = "/d/" + ZONE + "/";
	else
	    ZONE = "/";

	// �л�������״̬
	change_status(QUEST_READY);

	// ������������ʱ�䣺30����
	set("live_time", 1800);

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

	if (objectp(NPC_OB))
	{
		NPC_OB->delete_temp("override/destruct");
		destruct(NPC_OB);
	}

	// ��������
	::cancel_quest();
}

// ����NPC����
void npc_destructed()
{
	call_out("cancel_quest", 0);
}

// ѯ��NPC
string ask_npc(object knower, object me)
{
	mapping my = query_entire_dbase();

	if (! objectp(NPC_OB))
		return CYN "��������ͷ����ͷ��û�к��£�С����Ҫ�͵��ˡ�" NOR;

	return CYN "������˵����" + PLACE + "���������˺���ɶ��ˡ�" NOR;
}

// �������
string query_introduce(object knower)
{
	mapping my = query_entire_dbase();

	switch (TYPE)
	{
	case 0:
		return "��˵��͢����ͨ������" + NPC_NAME +
		       "�����������Ӵ��ˣ����췴��";
	case 1:
		return "��˵�ٸ�����׽�÷���" + NPC_NAME +
		       "����һ�ɲ��Ǻ��˰���";
	}
}

void do_say(object knower)
{
	mapping my = query_entire_dbase();

	message_vision("$N����������������Ǳ��ٸ�׽�õĶ�û���³����㿴��" +
		       NPC_NAME + "��ô�ݣ���Ҳ��С���͵��ˣ�\n", knower);
}

// �����Ϣ�ܹ���ɢ����
int can_know_by(object knower)
{
	mapping my = query_entire_dbase();
	string fname;

	fname = file_name(environment(knower));
	if (! stringp(ZONE) || strlen(ZONE) < 1 ||
	    ZONE == fname[0..strlen(ZONE) - 1])
		// ��С����ͬһ������
		return 1;

	return 0;
}

// �ǼǸ��������Ϣ
void register_information()
{
	mapping my = query_entire_dbase();

	if (! clonep() || ! mapp(my))
		// �����������Բ��Ǽ�
		return;

	set_information(NPC_NAME, (: ask_npc :));
	set_information(NPC_ID, (: ask_npc :));
}
