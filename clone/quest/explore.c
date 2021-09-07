// �������explore.c

#include <ansi.h>
#include <quest.h>
#include <command.h>

inherit QUEST_OB;

#define NPC_OB	  my["npc"]       // ���ձ����NPC����
#define NPC_NAME	my["npc_name"]  // ���ձ����NPC������
#define NPC_ID	  my["npc_id"]    // ���ձ����NPC��ID
#define ENV_OB	  my["env_ob"]    // �������صĵص�
#define QOB	     my["qob"]       // ���ձ�����ļ�����
#define QOB_NAME	my["qob_name"]  // ���ձ��������
#define ZONE	    my["zone"]      // ���ն�������������

object search_qob(object me);
int    npc_accept_object(object me, object who, object ob);
void   npc_destructed();

// ������󴴽�
void create()
{
	seteuid(getuid());
	setup();
}

// ����һ������
// ����һ����Ʒ����Ѱ�ң��Զ�������������������ص㣬����ɱ
// �˵�һ���˼��ɻ�ø���Ʒ��Ȼ�󽻸��ڶ�������ȡ������
void init_quest(object npc_ob, string qob_name, string zone, string *files)
{
	mapping my;
	string room;
	object env;
	object qob;

	my = query_entire_dbase();

	// �������������
	set_name(npc_ob->name() + "����");

	if (npc_ob->query_temp("quest_ob"))
	{
		// ���NPC�Ѿ���������������ֹ����
		destruct(this_object());
		return;
	}

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

	NPC_OB = npc_ob;
	NPC_NAME = npc_ob->name();
	NPC_ID = npc_ob->query("id");
	QOB    = qob;
	QOB_NAME = qob->name();
	ZONE = zone;

	// ���ѡ��һ���ص�
	for (;;)
	{
		call_other(room = zone + files[random(sizeof(files))], "???");
		if (! objectp(env = find_object(room)))
		{
			// �޷�ȡ���������
			cancel_quest();
			return;
		}

		if (mapp(env->query("exits")))
			// �ҵ����г��ڵķ���
			break;
	}

	// �ڷ����з��ÿ������Ķ��󣬲�ȥ���÷�������ҵ���
	// ������ͭ��
	env->set_temp("no_search", ([ "/clone/money/coin" : 0,
				      "/clone/money/silver" : 0, ]));
	env->set_temp("search_objects", ([ (: search_qob :) : 10000 ]));
	env->set_temp("been/searched", -150);
	ENV_OB = env;

	// ����NPC�ĶԻ���Ϣ
	npc_ob->set("inquiry/" + NPC_NAME, "�����������£�");
	npc_ob->set("inquiry/" + NPC_ID, "���Ұ������Ҷ����ˣ�");
	npc_ob->set("inquiry/" + QOB_NAME, "������...��֪��ô������ң�");
	npc_ob->set_temp("quest_ob", this_object());

	// ���ý�����Ʒ����Ϣ������NPC���ڵ�ʱ�����������
	// ������ڣ���Ϊ����������ʱ������NPC�������Կ���
	// ��NPC���ñ��ص�"npc_accept_object"������
	npc_ob->set_temp("override/accept_object", (: npc_accept_object :));

	// ����������Ϣ��NPC���������Ժ��Զ��������
	npc_ob->set_temp("override/destruct", (: npc_destructed :));

	// �л�������״̬
	change_status(QUEST_READY);

	// ������������ʱ�䣺30����
	set("live_time", 1800);

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
	npc_ob->delete("inquiry/" + QOB_NAME);
	NPC_OB = 0;
}

// �ָ�ENV�����������ʱ�����ָ������Ļ���
void restore_env()
{
	mapping my = query_entire_dbase();
	object env;

	if (! objectp(env = ENV_OB))
		return;

	// ȥ����ʱ��������Ʒ��Ϣ
	env->delete_temp("search_objects");
	env->delete_temp("no_search");
	env->set_temp("been/searched", 30);
	ENV_OB = 0;
}

// ��������
void cancel_quest()
{
	mapping my = query_entire_dbase();

	// �ָ�NPC��Ȼ���������
	restore_npc();
	restore_env();

	if (objectp(QOB) && ! environment(QOB))
		destruct(QOB);

	::cancel_quest();
}

// ����NPC����
void npc_destructed()
{
	call_out("cancel_quest", 0);
}

// �ڷ���������Ʒ
object search_qob(object me)
{
	mapping my = query_entire_dbase();
	mapping dq;
	object ob;

	if (me->query("score") < 2000)
		// ������2000�Ľ����������ܹ��ҵ�
		return 0;

	if (! objectp(QOB))
		// �����Ʒ�Ѿ�û���ˣ��޷�����
		return 0;

	if (objectp(environment(QOB)))
		// ����Ʒ�Ѿ��������޷�����
		return 0;

	if (! environment(me)->query("no_fight") && random(100) < 10)
	{
		// �ҵ�ɱ��һ����
		ob = new("/clone/npc/killer");
		ob->move(environment(me));
		message_vision("ͻȻ�ܳ�һ����Ӱ����ݺݵĶ�$N"
			       "�������" + RANK_D->query_rude(me) +
			       "�����������ɶ�� ��\n", me);
		ob->kill_ob(me);
		return 0;
	}

	if (mapp(dq = me->query_temp("freequest")) &&
	    dq[this_object()])
	{
		// �����ѯ�ʹ�������񣬴�ʱ�Ϳ��Ի�ý���
		map_delete(dq, this_object());
		QUEST_D->delay_bonus(me, ([ "exp" : 100 + random(20),
					    "pot" : 30 + random(20),
					    "score" : 5 + random(4),
					    "prompt": "����Ѱ��" + QOB_NAME +
						      HIG "�Ĺ�����" ]));
	}

	return QOB;
}

// ѯ��NPC - ��Ҫ�ṩ��Ʒ����
string ask_npc(object knower, object me)
{
	mapping my = query_entire_dbase();

	if (! objectp(NPC_OB))
		return CYN "Ŷ����˵" HIY + NPC_NAME + NOR CYN
		       "��֪��ȥ�Ķ�ȥ�ˣ����ص�ʧ���ˡ�" NOR;

	return "��˵" + NPC_NAME + "�����һ�����������أ�";
}

// ѯ��QOB - �ṩ����Ʒ����Ϣ
string ask_qob(object knower, object me)
{
	mapping my = query_entire_dbase();
	mapping dq;
	object env;
	string exits;
	string *str;

	if (! objectp(QOB) || ! objectp(env = ENV_OB) && ! environment(QOB))
		return CYN "�ݿɿ�����Ϣ˵��" + QOB_NAME + CYN "��"
		       "��Ҳ�Ҳ����ˣ�����ôҲ�ǰ�æ���ˡ�" NOR;

	if (environment(QOB))
		return CYN "����˵�������Ѿ��ҵ�" + QOB_NAME +
		       CYN "�ˣ���������ô�Ͳ������أ�" NOR;

	if (me->query("score") >= 2000)
	{
		if (! mapp(env->query("exits")))
			exits = "û�г���";
		else
		{
			str = keys(env->query("exits"));
			str = map_array(str, (: GO_CMD->query_chinese_dir($1) :));
			str -= ({ 0 });
			exits = "��ž���" + implode(str, "��") + "����";
		}
	
		message("vision", knower->name() +
			"���˿����ܣ�����������" +
			me->name() + "����˵��Щʲô��\n",
			environment(me), ({ me }));
		tell_object(me, sort_msg(knower->name() + "���˿���"
			    "�ܣ����������������˵���������ǧ��"
			    "����߱���ѽ��������������������鱨��"
			    "�����Ҳ�ҪǮ�͸������ˣ���˵�Ǹ�������һ��" +
			    exits + "�ĵط�������������Ҳ����̫Զ�ء���"
			    "��������ϸ����û׼���з����أ���\n"));
		if (! mapp(dq = me->query_temp("freequest")))
			dq = ([ this_object() : 1 ]);
		else
			dq[this_object()] = 1;

		me->set_temp("freequest", dq);
	} else
		message_vision("$N�������µĴ�����һ��$n����"
			       "��¶��һ˿��м����̬��\n", knower, me);

	return CYN "��ʵ��˵��" HIY + QOB_NAME + NOR CYN
	       "������ɶ���أ��ܱȵ��ϼ��Ⱥ;ƴ�ô��" NOR;
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

	return CYN "��˵" + HIY + NPC_NAME + NOR CYN "��������Ѱ��" +
	       HIY + QOB_NAME + NOR CYN "����������ϧ��Ҫ���ꡣ" NOR;
}

// ������ʾ
string query_prompt()
{
	switch (random(3))
	{
	case 0:
		return CYN "����������Ŀ���̸�����" HIY + name() +
		       NOR CYN "������";
	case 1:
		return "�ޣ�¥��ס����Ǽ������˸ղ�˵ʲô��" HIY + name() +
		       NOR CYN "���ء�";
	default:
		return "ǰ������������������ʿ��һ�����Ǹ��֣�"
		       "���ǻ�˵�����" HIY + name() + NOR CYN "���ء�";
	}
}

void do_say(object knower)
{
	if (! objectp(knower) || ! living(knower))
		return 0;

	message_vision("$N���ʼ����������ͷ��¶�Ʋ��Ǻ��¡�"
		       "�㿴���ⲻ�����˰ɣ���\n", knower);
}

int npc_accept_object(object me, object who, object ob)
{
	mapping my = query_entire_dbase();
	mapping b;
	object reward;

	int exp;
	int pot;
	int score;
	int weiwang;

	if (ob->is_character() || ob->is_item_make())
		// ���������������ı���
		return 0;

	if (ob != QOB)
		return 0;

	if (me->is_fighting())
		return 0;

	if (base_name(environment(me)) != me->query("startroom"))
	{
		message_vision("$N����$n��һ���׳�ģ����\n", me, who);
		return -1;
	}

	message_sort("$N�ӹ�" + ob->name() + "��������ȥ���˿���ϲ��"
		     "��ʤ��һʱ���Ǽ�����֡����βŶ�$n��������λ" +
		     RANK_D->query_respect(who) +
		     "��ʵ���Ǹм����������С��˼�����Ц�ɣ���\n", me, who);
	message_vision("$N����$nһЩ�ƽ���Ϊ���ꡣ\n", me, who);
	reward = new("/clone/money/gold");
	reward->set_amount(1);
	reward->move(who, 1);

  //      CHANNEL_D->do_channel(this_object(), "rumor",
  //			    "��˵" + who->name(1) +
   //			   "(" + who->query("id") + ")��" +
   //			   me->name() + HIM + "�ҵ���" + QOB_NAME +
   //			   HIM "���쵽��������");

	// ����
	exp = 80 + random(40);
	pot = 20 + random(25);
	score = 15 + random(15);
	weiwang = 5 + random(5);

	b = ([ "exp" : exp,
	       "pot" : pot,
	       "score" : score,
	       "weiwang" : weiwang,
	       "prompt": "��Ѱ��" + QOB_NAME +
			 HIG "�Ĺ����У���������" ]);
	QUEST_D->delay_bonus(who, b);

	destruct(ob);
	call_out("cancel_quest", 0);
	return -1;
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
	set_information(QOB_NAME, (: ask_qob :));
}

// ���������Ա�ĳ��ɢ����
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
