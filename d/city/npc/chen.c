// chen.c

#include <ansi.h>

inherit NPC;
inherit F_DEALER;
string do_answer();
void create()
{
	set_name("���е�", ({ "chen youde", "chen" }));
	set("long", "���е���������ݹݳ���\n");
	set("gender", "����");
	set("age", 45);
	set("icon","00723");
	set_skill("dodge", 80);
	set_skill("force", 80);
	set_skill("parry", 80);
	set_skill("claw", 80);
	set_skill("hand", 80);
	set_skill("strike", 80);
	set_skill("finger", 80);
	set_skill("cuff", 80);
	set_skill("blade", 80);
	set_skill("club", 80);
	set_skill("staff", 80);
	set_skill("sword", 80);
	set_skill("throwing", 80);
	set_temp("apply/attack", 80);
	set_temp("apply/defense", 80);
	set_temp("apply/damage", 20);

	set("combat_exp", 400000);
	set("shen_type", 1);
	 set("inquiry", ([
		"��ָ�ϡ�" : (: do_answer :),
	      
			]));
	set("vendor_goods", ({
		"/clone/book/basic-sword",
		"/clone/book/basic-blade",
		"/clone/book/basic-dagger",
		"/clone/book/basic-unarmed",
		"/clone/book/basic-dodge",
		"/clone/book/basic-parry",
		"/clone/book/basic-force",
		"/clone/book/basic-staff",
		"/clone/book/basic-whip",
       		"/clone/book/basic-club",
		"/clone/book/basic-throwing",
	}));
	
	setup();
}

void init()
{
	add_action("do_buy", "buy");
	add_action("do_list", "list");
}

int accept_object(object who, object ob)
{
	if (who->query("combat_exp") >= 350000)
	{
		message_vision("���е�����$N˵������书Ӧ��"
			       "�������������ٳ�����������û�������ˡ�\n", who);
		return 0;
	}

	if (ob->query("money_id") && ob->value() >= 500)
	{
		who->set_temp("marks/yangzhou_paied",1);
		message_vision("���е¶�$N˵���ã���λ" + RANK_D->query_respect(who) + 
			       "��ѧʲô�أ�\n" , who);
		return 1;
	} else
		message_vision("���е���ü��$N˵��Ǯ�Ҳ��ں�"
			       "������Ҳ����Ҳ̫���˵���ɣ�\n", who);
	return 0;
}

int recognize_apprentice(object ob)
{
	if (! (int)ob->query_temp("marks/yangzhou_paied") == 1)
		return 0;

	return 1;
}
string do_answer()
{
  string str="";    
write(HIY"��������ݡ�"NOR"�����ڻ����书\n");
 printf(HIC"��"HIY"����������������������������������������������������������"HIC"��"NOR"\n");
str+="  ���������Ṧ (dodge)	    ����  ����ȭ�� (cuff) \n";
str+="  ���������ڹ� (force)	    ����  �������� (blade) \n";
str+="  ���������м� (parry)	    �������������� (stick) \n";
str+="  ��������צ�� (claw)	     �������������� (club) \n";
str+="  ���������ַ� (hand)	     �����������ȷ� (staff) \n";
str+="  ���������Ʒ� (strike)	   �������������� (sword) \n";
str+="  ��������ָ�� (finger)	   �������������� (throwing) \n";
    write(str);
    write(HIG"\n  ѧϰ������: xue ʦ���� �书����   <��ҪǮǮ,����5��> "NOR"\n");
 printf(HIC"��"HIY"����������������������������������������������������������"HIC"��"NOR"\n");

     return "����ҪѧЩʲô�أ�";
}