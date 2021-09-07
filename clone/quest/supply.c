// �������search.c

#include <ansi.h>
#include <quest.h>

inherit QUEST_OB;

#define NPC_OB	  my["npc"]       // ������Ʒ��NPC����
#define NPC_NAME	my["npc_name"]  // ������Ʒ��NPC������
#define NPC_ID	  my["npc_id"]    // ������Ʒ��NPC��ID
#define PLACE	   my["place"]     // ������Ʒ��NPC�ĵص�
#define SOB_FILE	my["sob_file"]  // ������Ʒ���ļ�����
#define SOB_NAME	my["sob_name"]  // ������Ʒ������
#define COUNT	   my["count"]     // ��Ҫ��Ʒ������
#define ZONE	    my["zone"]      // ���ն�������������

int  npc_accept_object(object me, object who, object ob);
void npc_destructed();

// ������󴴽�
void create()
{
	seteuid(getuid());
	setup();
}

// ����һ������
// ����һ����Ʒ����Ѱ�ң��Զ�������������������ص㣬����ɱ
// �˵�һ���˼��ɻ�ø���Ʒ��Ȼ�󽻸��ڶ�������ȡ������
void init_quest(object npc_ob, string sob_file)
{
	mapping my;

	my = query_entire_dbase();

	// �������������
	set_name(npc_ob->name() + "����");

	if (npc_ob->query_temp("quest_ob"))
	{
		// ���NPC�Ѿ���������������ֹ����
		destruct(this_object());
		return;
	}
	npc_ob->set_temp("quest_ob", this_object());

	// �漴������Ҫ����Ʒ����
	COUNT = 3 + random(6);

	// ��¼�����������Ϣ
	NPC_OB = npc_ob;
	NPC_NAME = npc_ob->name();
	NPC_ID = npc_ob->query("id");
	SOB_FILE = sob_file;
	SOB_NAME = sob_file->name();
	PLACE = environment(npc_ob)->short(1);
	if (sscanf(file_name(environment(npc_ob)), "/d/%s/%*s", ZONE) == 2)
	    ZONE = "/d/" + ZONE + "/";
	else
	    ZONE = "/";

	// ����NPC�ĶԻ���Ϣ
	npc_ob->set("inquiry/" + NPC_NAME, "�����������£�");
	npc_ob->set("inquiry/" + NPC_ID, "���Ұ������Ҷ����ˣ�");
	npc_ob->set("inquiry/" + SOB_NAME, "����������Ҫ��Щ��������ɴ����ˣ�");

	// ���ý�����Ʒ����Ϣ������NPC���ڵ�ʱ�����������
	// ������ڣ���Ϊ����������ʱ������NPC�������Կ���
	// ��NPC���ñ��ص�"npc_accept_object"������
	npc_ob->set_temp("override/accept_object", (: npc_accept_object :));

	// ����������Ϣ��NPC���������Ժ��Զ��������
	npc_ob->set_temp("override/destruct", (: npc_destructed :));

	// �л�������״̬
	change_status(QUEST_READY);

	// ������������ʱ�䣺15����
	set("live_time", 900);

	// �Ǽ�ҥ����Ϣ
	register_information();
}

// �ָ�NPC�����������ʱ�����ָ�������NPC
void restore_npc()
{
	mapping my = query_entire_dbase();
	object npc_ob;

	if (! objectp(npc_ob = NPC_OB))
		return;

	npc_ob->delete_temp("override/accept_object");
	npc_ob->delete_temp("override/destruct");
	npc_ob->delete("inquiry/" + NPC_NAME);
	npc_ob->delete("inquiry/" + NPC_ID);
	npc_ob->delete("inquiry/" + SOB_NAME);
	NPC_OB = 0;
}

// ��������
void cancel_quest()
{
	// �ָ�NPC��Ȼ���������
	restore_npc();

	::cancel_quest();
}

// ����NPC����
void npc_destructed()
{
	remove_call_out("cancel_quest");
	call_out("cancel_quest", 0);
}

// ѯ��NPC - ��Ҫ�ṩ��Ʒ����
string ask_npc(object knower, object me)
{
	mapping my = query_entire_dbase();

	if (! objectp(NPC_OB))
		return CYN "Ŷ����˵" HIY + NPC_NAME + NOR CYN
		       "��֪���㵽�Ķ�ȥ�ˣ��ö����������ء�" NOR;

	return "�����������������ֲ���ʶ�˼ң�";
}

// ѯ��SOB - �ṩ����Ʒ����Ϣ
string ask_sob(object knower, object me)
{
	mapping my = query_entire_dbase();

	return CYN "��" HIY + SOB_NAME + NOR CYN
	       "�ɲ������ǰ���Ӧ��մ�Ķ���ѽ����˵�ǲ��ǣ�" NOR;
}

// �������
string query_introduce(object knower)
{
	mapping my = query_entire_dbase();

	if (! objectp(NPC))
	{
		remove_call_out("do_say");
		call_out("do_say", 1);
	}

	return CYN "��˵" + PLACE + "��" + HIY + NPC_NAME + NOR CYN "����һ��" +
	       HIY + SOB_NAME + NOR CYN "���٣���˵�����ʲô��" NOR;
}

// ������ʾ
string query_prompt()
{
	switch (random(3))
	{
	case 0:
		return CYN "�����������Щ����˵��" HIY + name() +
		       NOR CYN "����";
	case 1:
		return "Ҳûʲô���£�ֻ����˵��" HIY + name() +
		       NOR CYN "���ˡ�";
	default:
		return "ǰ���컹���˼�˵��" HIY + name() +
		       NOR CYN "�ء�";
	}
}

void do_say(object knower)
{
	if (! objectp(knower) || ! living(knower))
		return 0;

	message_vision("$N���������Ҹ��㶼˵�ˣ�Ҫ��Щ����û��"
		       "�£��ⲻ�������˰ɣ���\n", knower);
}

int npc_accept_object(object me, object who, object ob)
{
	mapping my = query_entire_dbase();
	mapping b;

	int exp;
	int pot;
	int score;

	if (ob->is_character() || ob->is_item_make())
		// ���������������ı���
		return 0;

	if (ob->name() != SOB_FILE->name())
		return 0;

	if (me->is_fighting())
		return 0;

	if (base_name(environment(me)) != me->query("startroom"))
	{
		message_vision("$Nһ��ãȻ������$n��\n", me, who);
		return -1;
	}

	message_vision("$N��ϲ���ӹ�" + ob->name() + "���˿�����$n��������λ" +
		       RANK_D->query_respect(who) +
		       "���ܺã��ܺã���\n", me, who);
	COUNT--;

	message_vision("$N����$nһЩǮ��Ϊ���ꡣ\n", me, who);
	MONEY_D->pay_player(this_player(), SOB_FILE->query("value"));

	remove_call_out("do_notice");
	if (COUNT < 1)
	{
		// ���е���Ʒȫ���������ˣ�׼����������
		message_vision("$NĨ��Ĩͷ�ϵĺ�������������"
			       "ȫ�����ˣ����¿��湻���µġ���\n", me);
 //	       CHANNEL_D->do_channel(this_object(), "rumor",
  //				    "��˵" + who->name(1) +
  //				    "(" + who->query("id") + ")��" +
  //				    me->name() + HIM + "������" + SOB_NAME + "��");
		call_out("do_finish", 4);
		restore_npc();
		change_status("stopping");
	} else
		call_out("do_notice", 1 + random(3), me, who);

	// ����
	exp = 20 + random(20);
	pot = 10 + random(5);
	score = 8 + random(8);

	if (who->query("combat_exp") > 200000)
	{
		// ����̫�ߣ���������
		exp = exp / 2 + 1;
		pot = pot / 2 + 1;
		score = score / 2 + 1;

		if (who->query("combat_exp") > 400000)
		{
			// �ٴ���������
			exp = exp / 2 + 1;
			pot = pot / 2 + 1;
			score = score / 2 + 1;
		}
	}
	
	if (mapp(b = query("bonus/" + who->query("id"))))
	{
		// ���ڽ���������
		b["exp"] += exp;
		b["pot"] += pot;
		b["score"] += score;
	} else
	{
		b = ([ "exp" : exp,
		       "pot" : pot,
		       "score" : score,
		       "prompt": "������ΰ���" + me->name() +
				  "׼��" + ob->name() + "������" ]);
		set("bonus/" + who->query("id"), b);
		call_out("do_bonus", 2 + random(2), who->query("id"), who);
	}

	destruct(ob);
	return -1;
}

private void do_notice(object me, object who)
{
	mapping my = query_entire_dbase();

	if (! can_talk_with(me, who))
		return;

	message_vision("$N���˵�����ֶ�$n�������һ���Ҫ" +
		       chinese_number(COUNT) +
		       SOB_FILE->query("unit") +
		       SOB_NAME + "�Ź�����\n", me, who);
}

// ׼���������
private void do_finish()
{
	if (sizeof(query("bonus")) > 0)
	{
		call_out("do_finish", 4);
		return;
	}

	// �������Ѿ����
	cancel_quest();
}

// ��ĳ�˽���
private void do_bonus(string who_id, object who)
{
	mapping b;

	b = query("bonus/" + who_id);
	delete("bonus/" + who_id);

	if (! mapp(b) || ! objectp(who) || ! living(who))
		return;

	QUEST_D->bonus(who, b);
}

// �ǼǸ��������Ϣ
void register_information()
{
	mapping my = query_entire_dbase();

	if (! clonep() || ! mapp(my))
		// �����������Բ��Ǽ�
		return;

	set_information(NPC_NAME, (: ask_npc :));
	set_information(NPC_ID,   (: ask_npc :));
	set_information(SOB_NAME, (: ask_sob :));
}

// ���������Ա�ĳ��֪����
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
