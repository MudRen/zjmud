// �������deliver.c

#include <ansi.h>
#include <quest.h>

inherit QUEST_OB;

#define QOB	     my["qob"]
#define NPC1	    my["npc1"]
#define NPC2	    my["npc2"]
#define QOB_NAME	my["qob_name"]
#define QOB_UNIT	my["qob_unit"]
#define NPC1_NAME       my["npc1_name"]
#define NPC2_NAME       my["npc2_name"]
#define QOB_ID	  my["qob_id"]
#define NPC1_ID	 my["npc1_id"]
#define NPC2_ID	 my["npc2_id"]
#define PLACE1	  my["place1"]
#define PLACE2	  my["place2"]
#define AMOUNT	  my["amount"]

int npc_accept_object(object me, object who, object ob);
mixed ask_for_qob(object npc2, object qob, string qob_name);

// ������󴴽�
void create()
{
	setup();
}

// ����һ������
// �Զ�������������������ص㣬����һ����Ʒ�����ͻ���
// �ҵ���һ���˽ӵ���Ʒ��Ȼ���͸��ڶ�������ȡ������
void init_quest(string qob_name, int amount)
{
	string name;
	string place1, place2;
	object npc1, npc2;
	mapping my;
	object qob;

	if (objectp(qob = find_object(qob_name)))
	{
		if (objectp(qob->query_temp("quest_ob")))
		{
			// ����Ʒ�Ѿ����ڲ���������������������ܽ���
			destruct(this_object());
			return;
		}
	} else
		// ����������Ʒ
		qob = load_object(qob_name);

	// ��¼����Ʒ����������
	qob->set_temp("quest_ob", this_object());
	qob->set_amount(amount);

	// �������������
	name = "����" + filter_color(qob->name());
	set_name(name);

	// ������������ص�
	place1 = NPC_D->random_place(({ "����" }));
	place2 = NPC_D->random_place(({ "����", place1 }));

	// ���������������
	npc1 = new(CLASS_D("generate") + "/questnpc");
	npc2 = new(CLASS_D("generate") + "/questnpc");

	npc1->set_temp("quest_ob", this_object());
	npc2->set_temp("quest_ob", this_object());

	// ��¼��Щ����ص����Ʒ��Ϣ
	my = query_entire_dbase();

	QOB = qob;
	QOB_NAME = filter_color(qob->name());
	QOB_UNIT = qob->query("base_unit");
	NPC1 = npc1;
	NPC2 = npc2;
	PLACE1 = place1;
	PLACE2 = place2;
	NPC1_NAME = npc1->name();
	NPC2_NAME = npc2->name();
	QOB_ID = qob->query("id");
	NPC1_ID = npc1->query("id");
	NPC2_ID = npc2->query("id");
	AMOUNT = amount;
	
	// ��Ʒ���أ���֤�ͻ���NPC�õö��㹻������
	npc2->set_max_encumbrance(1000000);
	qob->move(npc2);

	// �������
	NPC_D->place_npc(npc1, 0, ({ place1 }));
	NPC_D->place_npc(npc2, 0, ({ place2 }));

	CHANNEL_D->do_channel(find_object(QUEST_D),"chat", place2 +"��"+npc2->name() +"�л���Ҫ�͸�"+ place1 +"��"+ npc1->name() +"��");
	// ���öԻ���Ϣ
	npc1->set("inquiry", ([
		name      : "���������������ģ�����ҡ�",
		QOB_NAME  : "��Щ����ѽ��������������������أ�",
		NPC1_NAME : "�����Ǳ��˰���",
		NPC2_NAME : "��ѽ����������Ӧ���������ģ�" ]));

	npc2->set("inquiry", ([
		name      : "û����Ը��ȥ��������������",
		QOB_NAME  : (: ask_for_qob, npc2, qob, qob->name() :),
		NPC1_NAME : "����������Ҫ�͸�����ѽ����������"+place1+"������",
		NPC2_NAME : "�����������кι�ɣ�" ]));

	// ���ý�����Ʒ����Ϣ������NPC���ڵ�ʱ�����������
	// ������ڣ���Ϊ����������ʱ������NPC�������Կ���
	// ��NPC���ñ��ص�"npc_accept_object"������
	npc1->set_temp("override/accept_object", (: npc_accept_object :));
	
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

	if (objectp(NPC1))
		destruct(NPC1);

	if (objectp(NPC2))
		destruct(NPC2);

	if (objectp(QOB))
		destruct(QOB);

	// ��������
	::cancel_quest();
}

// user ask npc2 for quest ob
mixed ask_for_qob(object npc2, object qob, string qob_name)
{
	object me;
	object ob;

	me = this_player();

	message_sort("$N���˿�$n��˵��������" + qob_name +
		     "���ͽ����Ұ������Ͱɣ��۰���׼ʱ��"
		     "������\n", me, npc2);
	tell_object(me, CYN "����" + npc2->name() +
			CYN "��" + qob_name +
			CYN "���и������͡�"NOR"\n");

	if (me->query("score") < 1000)
	{
		message_sort("$N�����۾�Ƴ��$nһ�ۣ�����һ����"
			     "������" + RANK_D->query_respect(me) + 
			     "����Ľ�������̫�ͣ������������Ҳ����ġ���\n",
			     npc2, me);
		return 1;
	}
	
	if (objectp(qob) && environment(qob) == npc2 && qob->query_amount())
	{
		if (me->query_encumbrance() + qob->weight() / qob->query_amount() <
		    me->query_max_encumbrance())
		{
			message_sort("$N������һ��$n�����ͷ����"
				       "���ðɣ����������Ƿǳ���Ҫ"
				       "�ģ���һ��Ҫ׼ʱ�͵�������\n", npc2, me);
			tell_object(me, HIG + npc2->name() +
					HIG "��һ" + 
					qob->query("base_unit") + qob_name +
					HIG "�������㡣"NOR"\n");

			ob = new(base_name(qob));
			qob->add_amount(-1);
			if (! objectp(ob))
				tell_object(me, "None ob.\n");
			ob->move(me, 1);
		} else
		{
			message_sort("$N�����۾�Ƴ��$nһ�ۣ�̾�˿�����������" + RANK_D->query_respect(me) + 
				     "�����������˵���ô����\n",
				       npc2, me);
		}
	} else
		message_sort("$N΢Ц�Ŷ�$n˵���������ͷ����ˣ�����" + qob_name +
			     "�Ѿ�������ȥ�ˣ���\n", npc2, me);

	return 1;
}

// ѯ��NPC1 - ���ջ������
string ask_npc1(object knower, object me)
{
	mapping my = query_entire_dbase();

	if (! objectp(NPC1))
		return CYN "������ô" HIY + NPC1_NAME + NOR CYN
		       "�ö˶˵ģ�" HIY + QOB_NAME + NOR CYN
		       "û�õ������������������ǿ�����" NOR;

	return CYN "Ŷ����ѽ����˵����" + PLACE1 + "�����˸�����ȥһ��" +
	       HIY + QOB_NAME + NOR CYN "�أ�" NOR;
}

// ѯ��NPC2 - ������Ʒ����
string ask_npc2(object knower, object me)
{
	mapping my = query_entire_dbase();

	if (! objectp(NPC2))
		return CYN "����˵" HIY + NPC2_NAME + NOR CYN
		       "��Ȼ����ɱ�ˣ�Ҳ��֪�����������ӵĻ���" NOR;

	if (me->query("score") < 500)
		call_out("do_whisper", 1, knower, me);

	return CYN "Ŷ����ѽ����˵����" + PLACE2 + "�����ŵ�" +
	       "�˰����ͻ��أ�" NOR;
}

// ֪ͨ���
void do_whisper(object knower, object me)
{
	if (! can_talk_with(knower, me))
		return;

	tell_object(me, WHT + knower->name() + WHT "���ĵĺ���"
		    "˵������ϧ��Ľ�������̫���ˣ�����������ˡ���\n");
	message("vision", knower->name() + "��" + me->name() +
		"�Ķ������ĵ�˵��Щʲô��\n", environment(me), ({ me }));
}

// ѯ��QOB - ��Ʒ����Ϣ
string ask_qob(object knower, object me)
{
	mapping my = query_entire_dbase();

	if (! objectp(QOB))
		return CYN "�Ѳ����Ѿ���ɽ����ȥ�ˣ���Ȼû��"
		       "֪����" HIY + QOB_NAME + NOR CYN "�������ˡ�" NOR;

	return CYN "��" HIY + QOB_NAME + NOR CYN + "ѽ��"
	       "�����Ǻ���ͨ��һ����������" NOR;
}

// �������
string query_introduce(object knower)
{
	mapping my = query_entire_dbase();

	return CYN "��˵" HIY + NPC2_NAME + NOR CYN "���轫һ��" +
	       HIY + QOB_NAME + NOR CYN "�͵�" HIY + NPC1_NAME + NOR
	       CYN "�Ķ�������û����Ȥ��" NOR;
}

// ������ʾ
string query_prompt()
{
	switch (random(3))
	{
	case 0:
		return CYN "�������������������˵��" HIY + name() +
		       NOR CYN "��������";
	case 1:
		return "Ҳûʲô���£�ֻ����˵��" HIY + name() +
		       NOR CYN "���°��ˡ�";
	default:
		return "ǰ���컹���˼�˵��" HIY + name() +
		       NOR CYN "�����ء�";
	}
}

int npc_accept_object(object me, object who, object ob)
{
	mapping my = query_entire_dbase();
	mapping b;
	object reward;
	int exp;
	int pot;
	int score;

	if (ob->is_character() || ob->is_item_make())
	{
		message_sort("$N����$n��ʹ����ҡ��ͷ��������Ҫ���ʲô����\n",
			     me, who);
		return 0;
	}
	
	if (ob->query("id") != QOB_ID)
	{
		message_sort("$N����$n��ʹ����ҡ��ͷ��������Ҫ���ʲô����\n",
			     me, who);
		return 0;
	}

	if (me->is_fighting())
		return 0;

	AMOUNT -= ob->query_amount();

	message_sort("$N���˿�����" + ob->name() + NOR 
		     "����$n�������ţ��������������" +
		     "����ȥ�ɡ�\n", me, who);
	reward = new("/clone/money/silver");
	reward->set_amount(ob->query_amount() / 1 + random(3));
	reward->move(who, 1);

	remove_call_out("do_notice");
	if (AMOUNT < 1)
	{
		// ���е���Ʒȫ���������ˣ�׼����������
		message_vision("$NĨ��Ĩͷ�ϵĺ�������������ȫ�˵��ˣ����¿��湻���µġ���\n", me);
		call_out("do_finish", 4);
		change_status("stopping");
	} else
		call_out("do_notice", 1 + random(3), me, who, ob);

	// ����
	exp = 10 + random(10);
	exp *= ob->query_amount();
	pot = 5 + random(5);
	pot *= ob->query_amount();
	score = 4 + random(4);
	score *= ob->query_amount();

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
				 "����" + ob->name() + "������" ]);
		set("bonus/" + who->query("id"), b);
		call_out("do_bonus", 2 + random(2), who->query("id"), who);
	}
	destruct(ob);
	return -1;
}

private void do_notice(object me, object who, object ob)
{
	mapping my = query_entire_dbase();

	if (! can_talk_with(me, who))
		return;

	message_vision("$N���˵�����ֶ�$n�������һ���Ҫ" +
		       chinese_number(AMOUNT) +
		       QOB_UNIT + QOB_NAME + "�Ź�����\n",
		       me, who);
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

	log_file("deliver", ctime(time())+":"+who->query("name")+"("+who->query("id")+")"+"���һ���ͻ�����\n");
	QUEST_D->bonus(who, b);
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
	set_information(QOB_NAME, (: ask_qob :));
	set_information(NPC1_ID, (: ask_npc1 :));
	set_information(NPC2_ID, (: ask_npc2 :));
	set_information(QOB_ID, (: ask_qob :));
}
