// ganjiang.c  �ɽ�
// Written by Doing Lu  1998/11/2

// �ɽ����������ߵĳ��������ǲ�������ҵ���Ʒ������������
// ����Ӧ�ú�Īа�򽻵������ player ��Īа���ｫһ��������
// �ף�Īа��ԭ�Ͻ����ɽ���ͨ��accept_object ���������ɽ���
// ���Ƴ���

// �ɽ����յ�Īа�����ĵ��ߣ���������ж������������Ժ���
// ���õ��ߵ������ߣ������ߵ�ID�������õ��ߵ���Ч���� point��
// ��Ϊ��Īа�����Ѿ������ˡ����ҵȺ� player ������ڵ��ߵ�
// ��Ϣ�������ʱ����������˵ı�־�������object������û�
// finish����ѯ�� player �Ƿ����������������ɵ����ļ�����
// �����ɵ����͸� player����������޸ġ�

inherit NPC;
inherit F_NOCLONE;

#include <ansi.h>

// ����ַ��������ó����ֵ����ʾ������ַ������зǷ��ĸ�ʽ
#define	ILLEGAL_STR	"."
// ��convertʱ����Ҫ��Ҫȥ����ɫ
#define	NOCOLOR		1
#define COLORABLE	0

private int	ask_me();				// ��ʾ������Ϣ
private int	show_order();				// ��ʾ������Ϣ
private int	start_work(object me, object ob);	// ��ʼ����
private int	prepare_make(object me, object ob);	// ��ʼ����
private void	clear_data();				// ��� ganjiang, moye, player ����ʱ������ȥ����������
private string  create_file(object item_temp);
private int     save_item_file(string filename, string content);
private void    tell_rules(object me);
private void    waiting(object me, object ob, object moye);
private string	converts(string arg, int max_len, int nocolor);
private string  prop_segment(mapping p, string path);
private int     save_item_file(string filename, string content);
private int     legal_chinese(string str);

void create()
{
	seteuid(getuid());

	set_name("�ɽ�", ({ "gan jiang", "ganjiang", "gan" }));
	set("long", "�����ô�׳�������������絶����͸��һ��Ӣ�������ǹ�������������������ʦ��\n" );

	set("nickname", HIR "��ʦ" NOR);
	set("gender", "����");
	set("attitude", "friendly");
	set("icon","05005");
	set("age", 1535);
	set("shen_type", 0);

	set("str", 1000);

	set("inquiry", ([
		"����" : (: ask_me :),
		"ԭ��" : "����͵���ԭ�ϣ�һ��Ǯ��һ�ֻ�����ԭ�Ͼ��ܳ��ö�����\n",
		"����" : "�����ٵúܣ��������ƽ�Ҫ�������뽻��Īа��\n",
		"�˻�" : "�Ǿ�...�˻�(discard)����...",
		"����" : (: show_order :),
			
	]));

	setup();

	set("startroom", "/d/item/xiaowu");
	check_clone();
	if (! this_object()) return;

	carry_object("/clone/misc/cloth")->wear();
}

void init()
{
	add_action("do_name", "name");
	add_action("do_name", "����");
	add_action("do_desc", "desc");
	add_action("do_desc", "����");
	add_action("do_wieldmsg", "wieldmsg");
	add_action("do_wieldmsg", "wearmsg");
	add_action("do_wieldmsg", "װ��");
	add_action("do_wieldmsg", "װ����Ϣ");
	add_action("do_unwield", "unwieldmsg");
	add_action("do_unwield", "removemsg");
	add_action("do_unwield", "����");
	add_action("do_unwield", "������Ϣ");
	add_action("do_finish", "finish");
	add_action("do_finish", "���");

	add_action("do_help", "help");
	add_action("do_help", "����");

	add_action("do_discard", "discard");
}

// ������ʾ��Ϣ
private int ask_me()
{
	message_vision("�ɽ���$N˵������Щ������Īа����ֻ��������\n", this_player());
	return 1;
}

int accept_object(object me, object ob)
{
	if (me->name(1) == "Īа")
	{
		if (me->query("id") != "mo ye")
		{
			command ("kick " + me->query("id"));
			message_vision("$N�ٺٵļ�Ц����������$n˵����"
				       "����Ϊȡ�������ӵ����־����ɱ�"
				       "�ң��һ�ûϹ�أ�\n",
				       this_object(), me);
			return 1;
		}
		start_work(ob->query("item/owner"), ob);
		return 1;
	}

	if (ob->query("item_origin"))
	{
		message_vision("�ɽ���$N˵���������ⶫ����������Ƚ�"
			       "��Īа���������︶��Ǯ��˵��\n", me);
		return 0;
	} else
	if (ob->is_item_make())
	{
		if (ob->item_owner() != me->query("id"))
		{
			command("heng");
			command("say ������Ķ�����û���ˣ�");
			destruct(ob);
			return 1;
		}
		message_vision("$N�ɻ������$n��������������"
			       "����ô���Ǿ��˵�(discard)�ɣ���\n",
			       this_object(), me);
		return 0;
	}

	message_vision("�ɽ�����Ķ�$N˵�����������Щ������ʲ"
		       "ô����������������Щ������\n", me);
	return 0;
}

private int start_work(object me, object ob)
{
	remove_call_out("prepare_make");
	call_out("prepare_make", 1, me, ob);
	set_temp("item/making", ob);
	set_temp("item/player", me);
	me->set_temp("item/status", "waiting");
	return 1;
}

private int prepare_make(object me, object ob)
{
	message_vision(HIC "\n$N˵�����ã���¯������"NOR"\n", this_object());
	message_vision(HIM "$N�ӹ�Īа���е�" + ob->name() +
		       HIM "�����ְ�������¯�ڣ���ʱ�䣬��" + ob->name() +
		       HIM "�ѱ���¯�е�����" HIR "����" HIM "��û��\n" +
		       "$N������¯����˵�������֮����Ϊ��Ѫ������"
		       "��֮�����������......"NOR"\n" , this_object());
	remove_call_out("work_step_1");
	call_out("work_step_1", 5, me, ob);
	return 1;
}

private int work_step_1(object me, object ob)
{
	message_vision(HIG "¯�𽥽���ת������ɫ�����粻����Ծ���������"
		       "��ʮ�����ȣ����Ǹɽ�Īа�������¡�"NOR"\n", this_object());
	if (objectp(me) && environment(me) == environment())
	{
		me->set_temp("item/can_help", 1);
		message_vision(HIW "$N��$n˵��������������ø��ã���"
			       "Ҫע���Լ��ľ���Ѫ�����������д��⣬��"
			       ZJURL("cmds:help")+ZJSIZE(15)"����"NOR+HIW"(help)һ��֮����\n\n", this_object(), me);
	}
	remove_call_out("work_step_2");
	call_out("work_step_2", 6, me, ob);
	return 1;
}

private int work_step_2(object me, object ob)
{
	message_vision(RED "¯�𵭵��İ������������ֳ�һƬ��ɫ......"NOR"\n", this_object());
	remove_call_out("work_step_3");
	if (objectp(me))
		me->delete_temp("item/can_help");
	call_out("work_step_3", 3, me, ob);
	return 1;
}

private int work_step_3(object me, object ob)
{
	message_vision(HIW "$N���ֳ���������һ�����Ѿ�ȡ����" + ob->name() +
		       HIW "�����ֳֽ�մ��۾��������������\n�����ģ�" + ob->name() +
		       HIW "�ڸɽ����µĳ���" + ob->query("item/ctype") +
		       HIW "����״��"NOR"\n", this_object());
	remove_call_out("work_step_4");
	call_out("work_step_4", 5, me, ob);
	return 1;
}

private int work_step_4(object me, object ob)
{
	message_vision(HIC "$N������ϣ����һ������" + ob->query("item/ctype") +
		       HIC "����ˮ�أ�ֻ��˿˿���죬��ˮ������һ��������"
		       "�������ܡ�"NOR"\n", this_object());
	remove_call_out("work_step_5");
	call_out("work_step_5", 3, me, ob);
	return 1;
}

private int work_step_5(object me, object ob)
{
	message_vision(HIW "$N�����Ĵ�ˮ�س�������õ�" + ob->query("item/ctype") +
		       HIW "���˿��������˵���ܺã��ܺá�"NOR"\n",
		       this_object());
	remove_call_out("work_step_6");
	call_out("work_step_6", 2, me, ob);
}

private int work_step_6(object me, object ob)
{
	object moye;
	int improve;

	if (! objectp(moye = present("mo ye",environment(this_object()))))
	{
		message_vision(HIW "�ɽ����˿����ܣ�˵�����ף�Īа�أ�"
			       "�������ˣ������ˣ�ȥ�ɣ�\n"
			       "�ɽ������õĵ����׽���¯���ʹ˲�����"NOR"\n",
			       this_object());
		if (objectp(me))
			me->delete_temp("item");

		if (objectp(ob) && present(ob, this_object()))
			destruct(ob);

		delete_temp("item");
		return 1;
	}

	if (! objectp(me))
		me = find_player(ob->query("item/owner_id"));

	if (! objectp(me) || environment(me) != environment())
	{
		message_vision(HIW "$N̾�˿�����˵��������Ϊ�����ȥ"
			       "�ˣ������˰��ˣ������ˣ�ȥ�ɣ�\n"
			       "$N�����õĵ����׽���¯���ʹ˲�����"NOR"\n",
			       this_object());
		if (objectp(me))
			me->delete_temp("item");

		if (objectp(ob) && present(ob, this_object()))
			destruct(ob);

		delete_temp("item");
		moye->delete_temp("item");
		return 1;
	}
	moye->set_temp("item/status", "waiting");
	me->set_temp("item/status", "inputing");
	message_vision("$N��$n˵����һ" + ob->query("item/unit") + "��" +
		       ob->query("item/ctype") + NOR "����û�����֣������������ְɣ�\n",
		       this_object(), me);

	tell_rules(me);

	// ������ߵ����֣�ID�����������ԣ��������õ��ߵļ�ֵ��������
	ob->set("item/long", "");
	ob->set("item/wield_msg", "");
	ob->set("item/wear_msg", "");
	ob->set("item/unwield_msg", "");
	ob->set("item/remove_msg", "");
	ob->set("item/owner_name", me->query("name"));
	ob->set("item/owner_id", me->query("id"));

	// ���õȴ�ʱ�䣬���3��
	set_temp("item/waited", 4);

	// �����ʱ����������
	remove_call_out("waiting");
	call_out("waiting", 240, me, ob, moye);
	return 1;
}

// ����������¯����ߵ��ߵȼ�
// Ҫ�󣺾� >= 180  �� >= 300  ������Ч�ȼ� >= 100  ���� >= 800 ������� >= 1000
// ������ķ� 200 ��������������� 10%
int do_help(string arg)
{
	object me;
	object ob;

	me = this_player();
	if (me->query_temp("item/status") != "waiting")
	{
		return notify_fail("û��ʲôҵ��\n");
	}
	if (! me->query_temp("item/can_help"))
	{
		if (arg) return 0;
		write("���ڲ������æ��ʱ��\n", me);
		return 1;
	}
/*
	if (me->query("jing") < 100)
	{
		message_vision(HIR "$N" HIR "��Хһ����˫�ִ���¯�ߣ���������"
			       "������¯��ͻȻ��ǰһ��..."NOR"\n", me);
		tell_object(me, RED "��е�����˥�ߡ�"NOR"\n");
		me->set("jing", 0);
		return 1;
	}
	me->receive_damage("jing", 80);
	if (me->query("qi") < 100)
	{
		message_vision(HIR "$N" HIR "��Хһ����˫�ִ���¯�ߣ���������"
			       "������¯��ͻȻ��ǰһ��..."NOR"\n", me);
		tell_object(me, RED "��е��������̡�"NOR"\n");
		me->set("qi", 0);
		return 1;
	}
	me->receive_damage("qi", 80);
*/
	if (me->query("neili") < 200 || me->query("max_neili") < 200)
	{
		message_vision(HIR "$N" HIR "��Хһ����˫�ִ���¯�ߣ���������"
			       "������¯��ͻȻ��ǰһ��..."NOR"\n", me);
		tell_object(me, RED "��е������ݽߡ�"NOR"\n");
		me->set("neili", 0);
		return 1;
	}
	message_vision(HIR "$N" HIR "��Хһ����˫�ִ���¯�ߣ�ɲ�Ǽ䣬¯����ڣ�"
		       "һ��" HIW "�׹�" HIR "��ֱ��������"NOR"\n", me);

	ob = query_temp("item/making");
	ob->add("item/point", ob->query("item/point") * 6 / 5);
	me->delete_temp("item/can_help");
	me->add("max_neili", -200);
	me->add("neili", -200);
tell_object(me,"����������������200�㣬���Ǵ���Ʒ��������"+ob->query("item/point") * 6 / 5+"�㡣\n");
	return 1;
}

private int show_order()
{
	object me;

	me = this_player();
	if (me->query_temp("item/status") != "inputing")
	{
		message_vision("$N������������������$n��\n",
			       this_object(), me);
		return 1;
	}

	tell_rules(me);
	return 1;
}

void tell_rules(object me)
{
	tell_object(me, ZJOBLONG"�ɽ������������˵����"ZJBR
			"������Ҫ��������������Ϣϵͳ��ȱʡ����������ȻҲ���������Լ�Ϊ���Զ�������"
			"��Ȼ�ˣ���ò����ñ������Ĵ����־��ޡ�����ķ������£�\n"ZJOBACTS2
			"����(������):name"ZJSEP
			"����(�ɡ�ѡ):desc"ZJSEP      
			"װ��ʱ����(�ɡ�ѡ):wieldmsg"ZJSEP
			"����ʱ����(�ɡ�ѡ):unwieldmsg"ZJSEP
			"�����趨:finish\n"
		);
}

void waiting(object me, object ob, object moye)
{
	if (! objectp(me))
		me = find_player(ob->query("item/owner_id"));

	if (! objectp(me))
	{
		message_vision("$N̾�˿���˵������ô�����ˣ�������"
			       "�ˣ�ȥ�ɣ�\n", this_object());
		if (objectp(moye))
			moye->delete_temp("item");

		delete_temp("item");
		destruct(ob);
		return;
	}

	if (add_temp("item/waited", -1) <= 0)
	{
		// �ȴ���ʱ
		if (objectp(moye))
			moye->delete_temp("item");

		log_file("static/item", sprintf("%s %s do timeout when make item of %s\n",
				 log_time(), log_id(me),
				 (ob ? filter_color(ob->name(1)) : "???")));
		if (objectp(ob) && present(ob, this_object()))
			destruct(ob);

		me->delete_temp("item");
		delete_temp("item");
		if (in_input(me)) return;
		if (environment(me) == environment())
		{
			message_vision("$N������üͷ˵����������ô��ô"
				       "ĥ�䣬���ˣ���Ҫ�Ͳ�Ҫ�ɣ�\n",
				       this_object());
			return;
		}
		message_vision("$N������üͷ��$n˵������������ô��ô"
			       "ĥ�䣬��Ҫ�����ˣ�ˡ���˿\n",
			       this_object(), me);
		return;
	}

	if (environment(me) != environment())
	{
		message_vision("$N�ɻ��˵��������ô�ܵ��ˣ����ˣ��ٵ�"
			       "��һ��ɡ�\n", this_object());
	} else
	if (! in_input(me))
	{
		message_vision(HIR "$N" HIR "��$n" HIR
			       "������㣬��㣬��ĥ�䣬�����ҿɾͲ����ˡ�"NOR"\n",
			       this_object(), me);
	}

	remove_call_out("waiting");
	call_out("waiting", 300, me, ob, moye);
}

private void clear_data()
{
	object me;
	object ob;
	object moye;

	if (objectp(moye = present("mo ye",environment(this_object()))))
		moye->delete_temp("item");

	if (objectp(ob = query_temp("item/making")))
		destruct(ob);

	if (objectp(me = query_temp("item/player")))
		me->delete_temp("item");

	delete_temp("item");
	remove_call_out("waiting");
}

int do_name(string arg)
{
	object me;
	object ob;
	string pname;
	string sname, sid;

	me = this_player();
	if (me->query_temp("item/status") != "inputing")
		return notify_fail("�㻹û���������أ�\n");

	if (!arg)
	{
		write(INPUTTXT("���������趨�ġ��������� Ӣ�����֡���","name $txt#")+"\n");
		return 1;
	}

	if (sscanf(arg, "%s %s", sname, sid) != 2)
	{
		write(INPUTTXT("��ʽ���ԣ����������趨�ġ��������� Ӣ�����֡���","name $txt#")+"\n");
		return 1;
	}

	// ILLEGAL_STR = "." ��ʾ�Ƿ�������
	if ((sname = converts(sname, 14, COLORABLE)) == ILLEGAL_STR)
	{
		write(INPUTTXT("��ʽ���ԣ����������趨�ġ��������� Ӣ�����֡���","name $txt#")+"\n");
		return 1;
	}

	if ((sid = converts(sid, 8, NOCOLOR)) == ILLEGAL_STR)
	{
		write(INPUTTXT("��ʽ���ԣ����������趨�ġ��������� Ӣ�����֡���","name $txt#")+"\n");
		return 1;
	}

	if (! sname || ! sid)
	{
		message_vision("$Nҡҡͷ����$n�������в��У���úø��������֣�\n",this_object(), me);
		write(INPUTTXT("��ʽ���ԣ����������趨�ġ��������� Ӣ�����֡���","name $txt#")+"\n");
		return 1;
	}

	if (file_size(ITEM_DIR + me->query("id")[0..0] + "/" +
		      me->query("id") + "-" + sid + ".c") != -1)
	{
		message_vision("$Nҡҡͷ����$n�������ã��㲻Ҫ����(" + sid + ")���Ӣ�Ĵ����ˣ���һ���ɣ�\n",
			       this_object(), me);
		write(INPUTTXT("�������������趨�ġ��������� Ӣ�����֡���","name $txt#")+"\n");
		return 1;
	}
	if(sid==me->query("id"))
	{
		message_vision("$Nҡҡͷ����$n���������Ժ���ͬ������(" + sid + ")Ӣ�Ĵ��Ż��˰ɣ�\n",
			       this_object(), me);
		write(INPUTTXT("�������������趨�ġ��������� Ӣ�����֡���","name $txt#")+"\n");
		return 1;
	}
	if (! is_chinese(filter_color(sname)))
	{
		command("kick " + me->query("id"));
		command("say ����д��������ô�ģ�");
		write(INPUTTXT("�������������趨�ġ��������� Ӣ�����֡���","name $txt#")+"\n");
		return 1;
	}

	if (! is_legal_id(sid))
	{
		command("say Ӣ�Ĵ��ű���ȫ����СдӢ�Ĳſ��ԣ�");
		write(INPUTTXT("�������������趨�ġ��������� Ӣ�����֡���","name $txt#")+"\n");
		return 1;
	}

	if (strlen(filter_color(sname)) < 4)
	{
		command("say ��˵�����������Ҳ̫���˰ɣ������������֣�");
		write(INPUTTXT("�������������趨�ġ��������� Ӣ�����֡���","name $txt#")+"\n");
		return 1;
	}

	if (strlen(sid) < 3)
	{
		command("say ��˵����������Ҳ̫���˰ɣ����������ַ���");
		write(INPUTTXT("�������������趨�ġ��������� Ӣ�����֡���","name $txt#")+"\n");
		return 1;
	}

	if (sname[0] == 27 && sname[4] == 'm')
	{
		// Add color prefix
		sname = NOR + sname;
	}

	ob = query_temp("item/making");
	ob->set("item/name", sname);
	ob->set("item/id", sid);

	write("���֣�" CYN + sname + "    ���ţ�" CYN + sid + NOR "\n");
	return 1;
}

int do_desc(string arg)
{
	object ob;
	object me;
	string chk;

	me = this_player();
	if (me->query_temp("item/status") != "inputing")
		return notify_fail("�㻹û���������أ�\n");

	ob = query_temp("item/making");
	if (! ob->query("item/name"))
	{
		message_vision("$N����$nһ�۵����㻹���ȸ���ȡ�������ٿ��������ɣ�\n",this_object(), me);
		return 1;
	}

	if (! arg)
	{
		write("���ո�ʽ��һ�ѷ�����$n\\n������������������ -- ����\\n��ʾ���У�$n������ߡ�\n");
		write(INPUTTXT("���������趨�ġ���������","desc $txt#")+"\n");
		return 1;
	}

	if ((arg = converts(arg, 200, COLORABLE)) == ILLEGAL_STR)
		return 1;

	arg = replace_string(arg, "$N", me->name(1));

	chk = filter_color(arg);
	if (strlen(chk) >= 2 && chk[0..1] == "��" || strsrch(chk, "\\n��") != -1)
	{
		write(INPUTTXT("���������趨�ġ���������","desc $txt#")+"\n");
		return notify_fail("�Բ������������ԡ��㡱�ִ�ͷ��\n");
	}

	chk = replace_string(chk, " ", "");
	chk = replace_string(chk, "\\n", "");
	chk = replace_string(chk, "$n", "");
	if (! legal_chinese(chk))
	{
		write(INPUTTXT("���������趨�ġ���������","desc $txt#")+"\n");
		return notify_fail("�Բ�����������ʹ�ú��ֺ�ϵͳ�涨����ʹ�õĴ�����š�\n");
	}

	arg = replace_string(arg, "$n", ob->query("item/name"));
	arg = replace_string(arg, "\\n", "\n");
	arg = chinese_desc(arg);
	ob->set("item/long", arg);
	write(CYN "����۲�����ʱ�򽫻��������������"NOR"\n" + arg + "\n");
	return 1;
}

int do_wieldmsg(string arg)
{
	object ob;
	object me;
	string chk;

	me = this_player();
	if (me->query_temp("item/status") != "inputing")
		return notify_fail("�㻹û���������أ�\n");

	ob = query_temp("item/making");
	if (! ob->query("item/name"))
	{
		message_vision("$N����$nһ�۵����㻹���ȸ���ȡ�������ٿ��������ɣ�\n",this_object(), me);
		return 1;
	}

	if (! arg)
	{
		write("���ո�ʽ��$N����һ�������һ�ѷ��������� -- ����$N��ʾ���Լ���$n������ߡ�\n");
		write(INPUTTXT("���������趨�ġ�װ����������","wieldmsg $txt#")+"\n");
		return 1;
	}

	if ((arg = converts(arg, 200, COLORABLE)) == ILLEGAL_STR)
	{
		write(INPUTTXT("��ʽ�����������������趨�ġ�װ����������","wieldmsg $txt#")+"\n");
		return 1;
	}

	chk = filter_color(arg);
	if (strlen(chk) >= 2 && chk[0..1] == "��" || strsrch(chk, "\\n��") != -1)
	{
		write(INPUTTXT("���������趨�ġ�װ����������","wieldmsg $txt#")+"\n");
		return notify_fail("�Բ������������ԡ��㡱�ִ�ͷ��\n");
	}

	chk = replace_string(chk, " ", "");
	chk = replace_string(chk, "\\n", "");
	chk = replace_string(chk, "$N", "");
	chk = replace_string(chk, "$n", "");
	if (! legal_chinese(chk))
	{
		write(INPUTTXT("���������趨�ġ�װ����������","wieldmsg $txt#")+"\n");
		return notify_fail("�Բ�����������ʹ�ú��ֺ�ϵͳ�涨����ʹ�õĴ�����š�\n");
	}

	// ���ﲻ������������װ�����������ļ�ʱ�Զ�ѡ��һ����Ϣ
	arg = chinese_desc(arg);
	arg = replace_string(arg, me->name(1), "$N");
	ob->set("item/wear_msg", arg);
	ob->set("item/wield_msg", arg);
	arg = replace_string(arg, "\\n", "\n");
	arg = replace_string(arg, "$N", me->name(1));
	arg = replace_string(arg, "$n", ob->query("item/name"));
	write(CYN "����װ������ʱ�򽫻��������������"NOR"\n" + arg + "\n");
	return 1;
}

int do_unwield(string arg)
{
	object ob;
	object me;
	string chk;

	me = this_player();
	if (me->query_temp("item/status") != "inputing")
		return notify_fail("�㻹û���������أ�\n");

	ob = query_temp("item/making");
	if (! ob->query("item/name"))
	{
		message_vision("$N����$nһ�۵����㻹���ȸ���ȡ�������ٿ��������ɣ�\n",
			       this_object(), me);
		return 1;
	}

	if (! arg)
	{
		write("�ο���ʽ��$N����һ�ӣ�$n�������ڡ� -- ����$N��ʾ���Լ���$n������ߡ�\n");
		write(INPUTTXT("���������趨�ġ��ջ���������","unwieldmsg $txt#")+"\n");
		return 1;
	}

	if ((arg = converts(arg, 200, COLORABLE)) == ILLEGAL_STR)
	{
		write(INPUTTXT("��ʽ�����������������趨�ġ��ջ���������","unwieldmsg $txt#")+"\n");
		return 1;
	}

	chk = filter_color(arg);
	if (strlen(chk) >= 2 && chk[0..1] == "��" || strsrch(chk, "\\n��") != -1)
	{
		write(INPUTTXT("�������������趨�ġ��ջ���������","unwieldmsg $txt#")+"\n");
		return notify_fail("�Բ������������ԡ��㡱�ִ�ͷ��\n");
	}

	chk = replace_string(chk, " ", "");
	chk = replace_string(chk, "\\n", "");
	chk = replace_string(chk, "$N", "");
	chk = replace_string(chk, "$n", "");
	if (! legal_chinese(chk))
	{
		write(INPUTTXT("�������������趨�ġ��ջ���������","unwieldmsg $txt#")+"\n");
		return notify_fail("�Բ�����������ʹ�ú��ֺ�ϵͳ�涨����ʹ�õĴ�����š�\n");
	}

	// ���ﲻ������������װ�����������ļ�ʱ�Զ�ѡ��һ����Ϣ
	arg = chinese_desc(arg);
	arg = replace_string(arg, me->name(1), "$N");
	ob->set("item/unwield_msg", arg);
	ob->set("item/remove_msg", arg);
	arg = replace_string(arg, "\\n", "\n");
	arg = replace_string(arg, "$N", me->query("name"));
	arg = replace_string(arg, "$n", ob->query("item/name"));
	write(CYN "�����ջ�����ʱ�򽫻��������������"NOR"\n" + arg + "\n");
	return 1;
}

// �ж��Ƿ��ǺϷ��ĺ���
private int legal_chinese(string str)
{
	int i;

	if (strlen(str) < 2) return 0;

	for (i = 0; i < strlen(str); i++)
	{
		if (str[i] < 161 || str[i] == 255) return 0;
		if ((! (i % 2)) && str[i] >= 248) return 0;
	}

	return 1;
}

// ת���ַ����е���ɫ��־
private string converts(string arg, int max_len, int no_color)
{
	int i;

	// ȥ���ַ����еĿո����ţ����ⱻ�����������ƻ�
	arg = replace_string(arg, " ", ""); 
	arg = replace_string(arg, "\"", "'");

	for (i = 0; i < strlen(arg) - 1; i++)
	{
		if (arg[i] == '\\' && arg[i + 1] != 'n')
		{
			write("�ַ�'\\'����ֻ�ܸ���n�ַ���ʾ�س���\n");
			return ILLEGAL_STR;
		}
	}

	arg = replace_string(arg, ",", "��");
	arg = replace_string(arg, ":", "��");
	arg = replace_string(arg, "?", "��");

	if (no_color)
	{
		arg = replace_string(arg, "$BLK$", "");
		arg = replace_string(arg, "$RED$", "");
		arg = replace_string(arg, "$GRN$", "");
		arg = replace_string(arg, "$YEL$", "");
		arg = replace_string(arg, "$BLU$", "");
		arg = replace_string(arg, "$MAG$", "");
		arg = replace_string(arg, "$CYN$", "");
		arg = replace_string(arg, "$WHT$", "");
		arg = replace_string(arg, "$HIR$", "");
		arg = replace_string(arg, "$HIG$", "");
		arg = replace_string(arg, "$HIY$", "");
		arg = replace_string(arg, "$HIB$", "");
		arg = replace_string(arg, "$HIM$", "");
		arg = replace_string(arg, "$HIC$", "");
		arg = replace_string(arg, "$HIW$", "");
		arg = replace_string(arg, "$NOR$", "");
	} else
	{
		arg = replace_string(arg, "$BLK$", BLK);
		arg = replace_string(arg, "$RED$", RED);
		arg = replace_string(arg, "$GRN$", GRN);
		arg = replace_string(arg, "$YEL$", YEL);
		arg = replace_string(arg, "$BLU$", BLU);
		arg = replace_string(arg, "$MAG$", MAG);
		arg = replace_string(arg, "$CYN$", CYN);
		arg = replace_string(arg, "$WHT$", WHT);
		arg = replace_string(arg, "$HIR$", HIR);
		arg = replace_string(arg, "$HIG$", HIG);
		arg = replace_string(arg, "$HIY$", HIY);
		arg = replace_string(arg, "$HIB$", HIB);
		arg = replace_string(arg, "$HIM$", HIM);
		arg = replace_string(arg, "$HIC$", HIC);
		arg = replace_string(arg, "$HIW$", HIW);
		arg = replace_string(arg, "$NOR$", NOR);
		if (strlen(arg) < strlen(NOR) ||
		    arg[strlen(arg) - strlen(NOR)..<1] != NOR)
		{
			// append NOR at tail
			arg += NOR;
		}
	}
	if (strlen(arg) > max_len + 30 ||
	    strlen(filter_color(arg)) > max_len)
	{
		write("�Բ�������ַ���̫���ˣ��벻Ҫ���볬��" + chinese_number(max_len) +
		      "���ַ������ַ�����\n");
		// ��ʾ�Ƿ�������
		return ILLEGAL_STR;
	}
	return arg;
}

int do_finish(string arg)
{
	object me;
	object ob;
	object moye;
	string msg;

	me = this_player();
	if (me->query_temp("item/status") != "inputing")
		return notify_fail("�㻹û���������أ�\n");

	if (! objectp(ob = query_temp("item/making")))
	{
		// ���ݲ��ԣ�����������BUG��ɣ�Ҳ��������Ϊ�ɽ���update��
		write("ϵͳ���ϣ����ݲ�һ�£����޷�������Ƶ��ߣ�\n");
		me->delete_temp("item");
		delete_temp("item");
		if (objectp(moye = present("mo ye",environment(this_object()))))
			moye->delete_temp("item");

		// ����ʧ�ܣ�ֹͣ����
		return 0;
	}
	
	if (! ob->query("item/name"))
	{
		message_vision("$N����$nһ�ۣ�˵��������ô�ܲ��������"
			       "���֣���Ҫ�ǲ���Ҫ�˾����ˣ�\n",
			       this_object(), me);
		return 1;
	}

	if (! ob->query("item/id"))
	{
		message_vision("$N����$nһ�ۣ�˵��������ô�ܲ��������"
			       "���ţ���Ҫ�ǲ���Ҫ�˾����ˣ�\n",
			       this_object(), me);
		return 1;
	}

	if(arg == "y")
	{
		call_out("confirm_make",1,"y",ob,me);
		return 1;
	}
	// ��ʾ player �������Ϣ
	msg = sprintf("�ɽ���$N˵����ĵ����������£��뿴����û�д�\n");
	message_vision(msg, me);
	// ˽����Ϣ
	msg = sprintf("�������֣�%s   ����Ӣ�Ĵ��ţ�%s\n\n",
		      ob->query("item/name"), ob->query("item/id"));
	if (ob->query("item/long") != "")
		msg += sprintf(CYN "����������£�" NOR "\n%s\n\n", ob->query("item/long"));
	else
		msg += "����ȱʡ�����������\n";

	if (ob->query("item/wield_msg") != "")
		msg += sprintf(CYN "װ��ʱ�������£�" NOR "\n%s\n\n",
			       replace_string(ob->query("item/wield_msg"), "\\n", "\n"));
	else
		msg += "װ��ʱ����ȱʡ��������\n";

	if (ob->query("item/unwield_msg") != "")
		msg += sprintf(CYN "�ջ�ʱ�������£�" NOR "\n%s\n\n",
			       replace_string(ob->query("item/unwield_msg"), "\\n", "\n"));
	else
		msg += "�ջ�ʱ����ȱʡ��������\n";
		msg += "���û�����⣬�Ϳ���"ZJURL("cmds:finish y")+ZJSIZE(22)+CYN"ȷ��"NOR"�����ˡ�\n";
	msg = replace_string(msg, "$N", me->query("name"));
	msg = replace_string(msg, "$n", ob->query("item/name"));

	tell_object(me, msg);

	return 1;
}

void confirm_make(string arg, object ob, object me)
{
	object moye;
	string item_filename;

	if (! objectp(query_temp("item/making")))
	{
		command("kick " + me->query("id"));
		command("say ��̫ĥ���ˣ��������Ҳ����ˣ�ˡ���˻���");
		return;
	}

	if (arg != "y" && arg != "Y")
	{
		message_vision("$N�Ե������㻹���ٿ����ɣ�\n", this_object());
		return;
	}

	message_vision("$N��$n˵�����ã����Ͼͺã�\n",
		       this_object(), me);
	if (item_filename = create_file(ob))
	{
		// clear the old item's data
		DBASE_D->set_object_data(ob, 0);
		  destruct(ob);
		catch(call_other(item_filename, "???"));
		ob = find_object(item_filename);
		if (! ob)
		{
			message_vision("$Nһ������$n������Ǹ��Ǹ������һЩ���⣡\n",
				       this_object(), me);
		} else
		{
			ob->move(me, 1);
			ob->save();	     // Create the record in dbase
			message_vision("$N��" + ob->query("name") + "������$n��\n",
				       this_object(), me);
tell_object(me,HIR"ϵͳ��ʾ��ֻ�п�����װ���ſ��Ա��沢�ٻ�(summon)�����ڵ�����ʦ�ṩ�������"NOR"\n");
			log_file("static/item", sprintf("%s %s created  %s(%s) point(%d)\n",
				 log_time(), log_id(me),
				 filter_color(ob->name(1)), ob->query("id"),ob->query("point")));
		}
	}

	if (objectp(moye = present("mo ye", environment())))
		moye->delete_temp("item");

	me->delete_temp("item");
	delete_temp("item");
	remove_call_out("waiting");
}

// ���ɵ����ĵ�, ��Ҫһ���ĵ���ԭ�϶���
// �����Ժ��� ITEM_DIR/???.c Ȼ��ɾ���ɵ�ԭ�϶���, ����һ���µĵ��ߣ������ļ���

// ����ԭ�϶���������Ե�˵��(item/)
// ------ �û���������������
// name			���ߵ����ƣ� ����Ҫ
// id			���ߵ�ID��   ����Ҫ
// long			���ߵ�������ϵͳ�������ɵ���ʱ�Զ���ӹ�������ԭ�ϵ�����
// wield_msg		װ�����������������û��ϵͳ���Զ�����
// unwield_msg		�ջ�����ʱ������
// wear_msg		���ϻ���ʱ������
// unwear_msg		�ѵ�����ʱ������

// ------ �����û�����������
// owner_id		�����ߵ�ID
// owner_name	   �����ߵ�����
// unit			��λ
// type			���ߵ����� weapon �� armor
// stype		���ߵ������ weapon Ϊ sword, blade, whip, stick �� armor Ϊ armor
// ctype		���ߵ����������� weapon Ϊ ���������ޡ��� �� armor Ϊ ����
// value		���ߵļ�ֵ
// point		�˺���

// ------ ˵�����û������ĵ��ߵ�����
// item_make		1

private string create_file(object item_temp)
{
	string	buf;			// �����ļ��Ļ�����
	string	filename;
	string  desc;
	int	i;
	mapping info;
	string  ih;
	string  id;

	// �����ļ���
	id = item_temp->query("item/owner_id");
	filename = ITEM_DIR + id[0..0] + "/" + id + 
		   "-" + item_temp->query("item/id") + ".c";
	if (file_size(filename) != -1)
	{
		write("�޷����ɵ�������֪ͨ��ʦ����\n");
		return 0;
	}
	assure_file(filename);
	buf = "// ITEM Made by player(" + item_temp->query("item/owner_name") +
	      ":" + item_temp->query("item/owner_id") + ") " + filename + 
	      "\n// Written by GAN JIANG(Doing Lu 1998/11/2)\t" + ctime(time()) + "\n";
	info = item_temp->query("item");
	ih = up_case(info["stype"]);
	if (info["type"] == "weapon")
	{
		// �������������ļ�
		desc = "������" + item_temp->query("material_name") + "���ƶ��ɵ�һ" +
		       info["unit"] + info["ctype"] + "��\n";

		desc += info["long"];
		if (desc[strlen(desc) - 1] != '\n')
			desc += "\n";

		desc += info["ctype"] + "���Ͽ���һ��С�֣�" +
			info["owner_name"] + "(" + info["owner_id"] + ")\n";

		// �Զ��������Ϣ
		if (info["wield_msg"] == "")
		{
			info["wield_msg"] = HIC "$N" HIC "һ����Х������һ" +
					    info["unit"] + HIC "$n" HIC "��" NOR;
		}

		if (info["unwield_msg"] == "")
		{
			info["unwield_msg"] = "$N����һĨ��������$n��";
		}
		buf += "#include <ansi.h>\n";
		buf += "#include <weapon.h>\n\n";
		buf += "inherit " + ih + ";\n";
		buf += "inherit F_ITEMMAKE;\n\n";
		buf += "void create()\n{\n";
		buf += sprintf("\tset_name(\"%s\", ({ \"%s\" }));\n", 
				info["name"], info["id"]);
		buf += sprintf("\tset_weight(%d);\n", item_temp->query_weight() * item_temp->query("item/wscale") / 100);
		buf += sprintf("\tset(\"item_make\", 1);\n");
		buf += sprintf("\tset(\"unit\", \"%s\");\n", info["unit"]);
		buf += sprintf("\tset(\"long\", \"%s\");\n", desc);
		buf += sprintf("\tset(\"value\", %d);\n", info["value"]);
		buf += sprintf("\tset(\"point\", %d);\n", info["point"]);
		buf += sprintf("\tset(\"material\", \"%s\");\n", item_temp->query("material_attrib"));
		buf += sprintf("\tset(\"wield_msg\", \"%s\\n\");\n", info["wield_msg"]);
		buf += sprintf("\tset(\"unwield_msg\", \"%s\\n\");\n", info["unwield_msg"]);
		buf += sprintf("\tif (! check_clone()) return;\n\trestore();\n");
		buf += sprintf("\tinit_%s(apply_damage());\n", info["stype"]);
		buf += prop_segment(info["prop"], "");
		buf += sprintf("\n\tsetup();\n}\n\n");
		// �������������ļ����
	} else
	{
		// ���ɷ��������ļ�
		desc = "������" + item_temp->query("material_name") + "���ƶ��ɵ�һ" +
		       info["unit"] + info["ctype"] + "��\n";

		desc += info["long"];
		if (desc[strlen(desc) - 1] != '\n')
			desc += "\n";

		desc += info["ctype"] + "Ե�Ͽ���һ��С�֣�" +
			info["owner_name"] + "(" + info["owner_id"] + ")\n";

		// �Զ��������Ϣ
		if (info["wear_msg"] == "")
		{
			info["wear_msg"] = YEL "$N" YEL "װ��" +
					   info["name"] + YEL "��" NOR;
		}
		if (info["remove_msg"] == "")
		{
			info["remove_msg"] = YEL "$N" YEL "������" +
					     info["name"] + YEL "��" NOR;
		}
		buf += "#include <ansi.h>\n";
		buf += "#include <armor.h>\n\n";
		buf += "inherit " + ih + ";\n";
		buf += "inherit F_ITEMMAKE;\n\n";
		buf += "void create()\n{\n";
		buf += sprintf("\tset_name(\"%s\", ({ \"%s\" }));\n", 
				info["name"], info["id"]);
		buf += sprintf("\tset_weight(%d);\n", item_temp->query_weight() * item_temp->query("item/wscale") / 100);
		buf += sprintf("\tset(\"item_make\", 1);\n");
		buf += sprintf("\tset(\"unit\", \"%s\");\n", info["unit"]);
		buf += sprintf("\tset(\"long\", \"%s\");\n", desc);
		buf += sprintf("\tset(\"value\", %d);\n", info["value"]);
		buf += sprintf("\tset(\"point\", %d);\n", info["point"]);
		buf += sprintf("\tset(\"material\", \"%s\");\n", item_temp->query("material_attrib"));
		buf += sprintf("\tset(\"wear_msg\", \"%s\\n\");\n", info["wear_msg"]);
		buf += sprintf("\tset(\"remove_msg\", \"%s\\n\");\n", info["remove_msg"]);
		buf += sprintf("\tif (! check_clone()) return;\n\trestore();\n");
		if (! info["prop"])
			buf += sprintf("\tset(\"armor_prop/armor\", apply_armor());\n");
		else
			buf += prop_segment(info["prop"], "");
		buf += sprintf("\n\tsetup();\n}\n\n");
		// ���ɷ��������ļ����
	}
	buf += sprintf("string long() { return query(\"long\") + item_long(); }\n");

	if (save_item_file(filename, buf) == 1)
		return filename;

	return 0;
}

// add mapping
private string prop_segment(mapping p, string path)
{
	string buf;
	string *ks;
	int i;

	buf = "";
	if (! p) return buf;

	ks = keys(p);
	for (i = 0; i < sizeof(ks); i++)
	{
		// check the paramter's type
		if (mapp(p[ks[i]]))
		{
			path += ks[i] + "/";
			buf += prop_segment(p[ks[i]], path);
		} else
			buf += sprintf("\tset(\"%s\", %s);\n",
				       path + ks[i], (string)p[ks[i]]);
	}

	return buf;
}

// filename ��д���ĵ������ƣ��Ѿ�������·��
// content ��д���ĵ�������
private int save_item_file(string filename, string content)
{
	rm(filename);
	if (write_file(filename, content))
	{
		return 1;
	} else
	{
		write("д�뵵��(" + filename + ")ʱ������֪ͨ��ʦ����\n");
		return 0;
	}
}

int do_discard(string arg)
{
	object money;
	object ob;
	object me;
	int n;

	if (! arg)
		return notify_fail("��ȥ�˻�ʲô������\n");

	me = this_player();
	if (! objectp(ob = present(arg, me)))
		return notify_fail("������û�����ֶ�����\n");

	message_vision("$n�ó�һ" + ob->query("unit") + ob->name() +
		       "��$N˵����������������˵���...��\n",
		       this_object(), me);

	if (! ob->is_item_make())
	{
		command("heng");
		command("say �ⲻ������������Ķ������ҿɲ��ܸ���");
		return 1;
	}

	if (ob->item_owner() != me->query("id"))
	{
		command("kick " + me->query("id"));
		command("say �����˱��˵Ķ����������������Ϊ����ɵ�ӣ�");
		return 1;
	}

	if (ob->weapon_level() >= 10000)
	{
		message_vision("$N�۾�һ�ɣ���$n���������ѷǷ�Ʒ���������٣���\n", this_object(), me);
		return 1;
	}

	command("sigh");
	command("say һǧ��������û��ʲô�����ҵĻ�ɫ���õģ����ˣ����ˣ�");
	message_vision("$N�ӹ�$n�ݹ�����" + ob->name() + "������"
		       "�ӽ��˻�¯�����������˰��Ρ�\n",
		       this_object(), me);
	command("say ���Ȼ�������ҵĶ�������Ҳ���������Ǯ��"
		"��Щ�������˻ظ���ģ�");
	n = (ob->query("value") * 8 / 10 + 9999) / 10000;
	if (! n)
	{
		money = new("/clone/money/silver");
		money->set_amount(1);
	} else
	{
		money = new("/clone/money/gold");
		money->set_amount(n);
	}
	message_vision("$N�ó�һЩ" + money->name() + "����"
		       "$n��\n", this_object(), me);
	log_file("static/item", sprintf("%s %s discard  %s(%s)\n",
				log_time(), log_id(me),
				filter_color(ob->name(1)), ob->query("id")));
	me->delete("can_summon/" + ob->query("id"));
	rm(base_name(ob) + ".c");
	DBASE_D->clear_object(ob);
	money->move(me, 1);
	return 1;
}
