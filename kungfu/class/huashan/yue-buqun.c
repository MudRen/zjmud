// yue-buqun.c lasted updated by cocacola on 2.19 for adding chushi
// ����Ⱥ

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

#include <ansi.h>
#include "qizong.h"

int  do_xunshan();
void check_weapon();
void unwield_weapon();
string ask_zixia();
mixed  ask_sanxian();

// ���ظ��˼�����������֤��quest��ʱ���������quest
int is_bad() { return 0; }
int is_good() { return 1; }

void create()
{
	set_name("����Ⱥ", ({ "yue buqun", "yue" }) );
	set("title", "��ɽ������");
	set("nickname", HIC "���ӽ�" NOR);
	set("gender", "����");
	set("class", "swordsman");
	set("age", 55);
	set("long", "����Ⱥ����ִ�ƻ�ɽ�ɣ��˵���������һ��һ�ĸ��֡�\n");
	set("attitude", "peaceful");
	set("str", 26);
	set("con", 30);
	set("dex", 30);
	set("int", 28);

	set("max_qi", 5200);
	set("max_jing", 2600);
	set("neili", 6000);
	set("max_neili", 6000);
	set("jiali", 80);

	set("combat_exp", 1600000);
	set("xunshan", 1);
	set("apprentice_available", 3);

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: exert_function, "powerup" :),
		(: perform_action, "sword.cimu" :),
		(: perform_action, "sword.pi" :),
		(: check_weapon :),
	}));
	set("inquiry", ([
		"Ѳɽ"     : (: do_xunshan :),
		"��ϼ��" : (: ask_zixia  :),
		"��ϼ�ؼ�" : (: ask_zixia  :),
		"�ؼ�"     : (: ask_zixia  :),
		"�����������ɽ�" : (: ask_sanxian :),
	]));

	set_skill("unarmed", 120);
	set_skill("sword", 180);
	set_skill("force", 170);
	set_skill("parry", 160);
	set_skill("dodge", 150);
	set_skill("literate", 120);
	set_skill("huashan-sword", 170);
	set_skill("huashan-xinfa", 170);
	set_skill("zixia-shengong", 170);
	set_skill("huashan-quanfa", 120);
	set_skill("feiyan-huixiang", 160);
	set_skill("pixie-jian", 220);

	map_skill("sword", "pixie-jian");
	map_skill("parry", "pixie-jian");
	map_skill("force", "zixia-shengong");
	map_skill("unarmed", "huashan-quanfa");
	map_skill("dodge", "pixie-jian");

	set("no_teach", ([
		"zixia-shengong" : "��������������ˣ���"
				   "������ϼ�ؼ����Լ��ж��ɡ�",
		"pixie-jian"     : "�����������ּҵļҴ��书��"
				   "����ô���ܻ��أ�",
	]));

	set_temp("apply/attack", 220);
	set_temp("apply/dodge", 220);
	set_temp("apply/parry", 200);
	set_temp("apply/damage", 150);
	set_temp("apply/unarmed_damage", 150);
	set_temp("apply/armor", 200);

	create_family("��ɽ��", 13, "����");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "sword.cimu" :),
		(: perform_action, "sword.pi" :),
		(: perform_action, "sword.gui" :),
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
		(: check_weapon :),
	}));

	setup();

	set("book_count", 1);
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/cloth/cloth")->wear();
	carry_object("/clone/misc/pin");
}

void check_weapon()
{
	if (objectp(query_temp("weapon")))
		return;

	command("wield pin");
	set("chat_msg_combat", ({
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
		(: perform_action, "sword.cimu" :),
		(: perform_action, "sword.pi" :),
		(: perform_action, "sword.gui" :),
	}));
	set("chat_chance", 120);
	set("chat_msg", ({
		(: unwield_weapon :),
	}));
}

void unwield_weapon()
{
	command("unwield pin");
	delete("chat_chance");
	delete("chat_msg");
	set("chat_msg_combat", ({
		(: exert_function, "powerup" :),
		(: exert_function, "recover" :),
		(: perform_action, "sword.cimu" :),
		(: perform_action, "sword.pi" :),
		(: perform_action, "sword.gui" :),
		(: check_weapon :),
	}));
}

void attempt_apprentice(object ob)
{
	if( query("apprentice_available") ) {
		if( find_call_out("do_recruit") != -1 )
			command("say ������һ��һ������");
		else
			call_out("do_recruit", 2, ob);
	} else {
		command("say �Ϸ�����Ѿ������������ӣ���������ͽ�ˡ�");
	}
}

void do_recruit(object ob)
{
	if( !permit_recruit(ob) )
		return;

	if( (int)ob->query_int() < 23 )
		command("say �һ�ɽ���Խ���Ϊ�������ҿ�" +
			RANK_D->query_respect(ob)+"���ʺ���ѧ������");

	else {
		command("say �ã��ã��ã��ܺá�");
		command("recruit " + ob->query("id") );
	}
}

int recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
	add("apprentice_availavble", -1);
}

void reset()
{
	set("book_count", 1);
	set("apprentice_available", 3);
}

int do_xunshan()
{
	object me = this_player();
      	string date;

    	date = NATURE_D->game_time();
	sscanf(date, "%s��%*s��", date);

	if (me->query_temp("xunshan"))
	{
	       if (! me->query_temp("xunshan/chaoyang"))
	       {
		      	message_vision("$N����$n˵���㳯����ûȥ������"
				       "����Ѳ��ʲôɽ��\n", this_object(), me);
			return 1;
	       }
	       if (! me->query_temp("xunshan/lianhua"))
	       {
		      	message_vision("$N����$n˵����������ûȥ������"
				       "����Ѳ��ʲôɽ��\n", this_object(), me);
		      	return 1;
	       }
	       if (! me->query_temp("xunshan/yuntai"))
	       {
		      	message_vision("$N����$n˵������̨��ûȥ����������"
				       "Ѳ��ʲôɽ��\n", this_object(), me);
		      	return 1;
	       }
	       if (! me->query_temp("xunshan/sheshen"))
	       {
		      	message_vision("$N����$n˵������ôûȥ�����£�����"
				       "Ѳ��ʲôɽ��\n", this_object(), me);
		      	return 1;
	       }
	       if (! me->query_temp("xunshan/siguo"))
	       {
		      	message_vision("$N����$n˵���㵽��˼����ȥ�ˣ�����"
				       "Ѳ��ʲôɽ��\n", this_object(), me);
		      	return 1;
	       }
	       if (! me->query_temp("xunshan/yunu"))
	       {
		      	message_vision("$N����$n˵���㵽��Ů����滪ɽС��"
				       "ȥ�����ˣ�����Ѳ��ʲôɽ��\n",
				       this_object(), me);
		      	return 1;
	       	}
	       	message_vision("$N����$n˵�����������ˡ������ȥ"
			       "��Ϣȥ�ɡ�\n", this_object(), me);
	       	me->delete_temp("xunshan");		      
	       	me->add("combat_exp", 100 + random(100));
	       	return 1;
	}
	else
	{
	       if (query("xunshan") == date)
	       {
		      	message_vision("$N����$n˵�������Ѿ�����Ѳɽ"
				     "ȥ�ˡ������������ɡ�\n", this_object(), me);
		      	return 1;
	       }
	       if (me->query("family/family_name") != "��ɽ��")
	       {
		      	message_vision("$N����$n���һ�������ɵ��Ӳ���"
				     "Ѳɽ�����������ļ�ϸ��\n", this_object(), me);
		      	return 1;
	       } else
	       {
		      	set("xunshan", date);
		      	message_vision("$N����$n˵�����ɵ�������Ѳɽ���㣬�ܺã���"
				       "�ã������ȥѲɽ�ɡ�\n",
				       this_object(), me);
		      	me->set_temp("xunshan/start", 1);
		      	me->set_temp("xunshan/time", time());
		      	return 1;
	       }
	}
}

string ask_zixia()
{
	mapping fam;
	object ob;
	object me;

	me = this_player();
	if (fam = me->query("family")) 
	{
		if (fam["family_name"] == "��ɽ����")
			return "���������ǽ��ھ�ȻҲ�������������ˣ�";

		if (fam["family_name"] != "��ɽ��" && fam["family_name"] != "��ɽ����")
			return RANK_D->query_respect(me) +
			       "�뱾�ɺ��޹ϸ𣬺��������ɵ��ؼ���";
	}

	if (me->query_skill("huashan-xinfa", 1) < 120)
		return "��Ļ�ɽ�ķ���ѧ��������ӻ�Ҫʲô��ϼ�ؼ���";

	if (me->query("max_neili", 1) < 800)
		return "�������Ҳ̫���ˣ��ú���������Ҫ����ʲô��ϼ�񹦣�";

	if (query("book_count") < 1)
		return "�������ˣ������ؼ��Ѿ�����ȡ���ˡ�";

	add("book_count", -1);
	ob = new("/clone/book/zixia_book");
	ob->move(me, 1);
	if (me->query_skill("zixia-shengong", 1) < 20)
	{
		me->set_skill("zixia-shengong", 20);
	}
	return "�ðɣ��Ȿ����ϼ�ؼ������û�ȥ�ú��ж��������ڹ�������"
	       "������ǻ�ɽһ����";
}

mixed ask_sanxian()
{
	object me;
	int n;
	string msg;

	me = this_player();
	if (me->query("family/family_name") != query("family/family_name"))
		return "�������ģ��Ҵ���ʲô��";

	if (me->query("can_perform/huashan-sword/sanxian"))
		return "��ɲ�Ҫ������˵����";

	n = me->query_temp("ask_sanxian");
	switch (n)
	{
	default:
		n = 1;
		msg = "���������ǽ��ڵ�ĩ�������ܺ�������������ȣ�";
		break;

	case 1:
		n = 2;
		msg = "�����������ڵ�����;֪�����������ϳ��ڹ����⽣��Ҳ�Ͳ���������;�ˡ�";
		break;

	case 2:
		n = 3;
		msg = "������Ȼ�������û������Ϊ�ף���ô����Ī��Ч�ã�";
		break;

	case 3:
		n = 4;
		msg = "������������������ڵ�����������֮��ȫȻ���ð���";
		break;

	case 4:
		n = 5;
		msg = "������˵�����ˣ���ʱ�������ڵ����кü�������������֮�¡�";
		break;

	case 5:
		n = 6;
		msg = "���... ���... ��׷����ô���ʲô��";
		break;

	case 6:
		n = 7;
		msg = "�ú�ѧϰ�ڹ�ȥ������������ͣ�";
		break;

	case 7:
		n = 8;
		msg = "����... ��ѽ�㣬��֪��ʲô�ˣ�";
		break;

	case 8:
		n = 9;
		msg = "�����㶼֪���ˣ������ҵ�ȷ����ϸ�о������ž�������Ϊ...";
		break;

	case 9:
		n = 10;
		msg = "��Ҫ׷�ʰ�����Ϊ���ǻ�ɽ���վ��ǽ��ɣ��ڹ�Ϊ����������Ҫ����Ϊ�������";
		break;

	case 10:
		n = 11;
		msg = "��ѧ��... ������....";
		break;

	case 11:
		if (me->query_skill("zixia-shengong", 1) < 150)
			return "����ϼ����Ϊ������Ҫ�úô���ӣ�";

		if (me->query_skill("huashan-sword", 1) < 135)
			return "��Ļ�ɽ����ѧ��������ӣ������������ֽ̾�����";

		message_vision(HIY "$n" HIY "���˿����ܣ��������ˣ�����վ����������"
			       "���ݳ���������ʽ������˷�����˼��\n"
			       HIY "$n" HIY "���£�����������ѧ�����У��Ժ�Ͳ�����"
			       "���ɵ��������ˣ��ú���ȥ�ɡ�"NOR"\n",
		       me, this_object());
		tell_object(me, HIG "��ѧ���˶����������ɽ���"NOR"\n");
		if (me->can_improve_skill("sword"))
			me->improve_skill("sword", 90000);
		me->set("can_perform/huashan-sword/sanxian", 1);
		return 1;
	}

	me->set_temp("ask_sanxian", n);
	return msg;
}

void unconcious()
{
	die();
}
