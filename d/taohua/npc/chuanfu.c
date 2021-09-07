// chuanfu.c �ϴ���

#include <ansi.h>

inherit NPC;
int  chu_hai();
void goto_dao(object ob);

void create()
{
	set_name("�ϴ���", ({ "lao chuanfu","chuanfu" }));
	set("gender", "����");
	set("age", 56);
	set("long", @LONG
����һ���ϴ��򡣱�����˪������͸��һ˿�ƻ�����������������ǰ
����ȥ���һ�����������ӵ��һ�Ҵ󴬿��Գ�����
LONG );

	set("combat_exp", 100000);
	set("shen_type", 1);

	set("eff_qi", 2000);
	set("qi", 2000);
	set("max_neili", 1000);
	set("neili", 1000);
	set("jiali", 100);

	set_skill("force", 200);
	set_skill("unarmed", 400);
	set_skill("dodge", 200);
	set_skill("parry", 200);
	set("inquiry", ([
		"�һ���" : "�һ�������һȺ��ħ�������и�С��Ů��������������\n",
		"����" :   (: chu_hai :),
	]));

	setup();
	carry_object("/clone/misc/cloth")->wear();
 }

int chu_hai()
{
	object ob, myenv;

	ob = this_player();
	if (ob->query("family/family_name") == "�һ���")
	{
		message_vision("�ϴ���һ���֣������������ᴬ��\n",ob);
		message_vision("���ᴬ���$N���˴���һ������ê�����Ϳ����ˣ����ϴ���ȴû�ϴ�......\n", ob);
		myenv = environment (ob) ;
		ob->move ("/d/taohua/dahai");
		tell_object(ob, BLU "���ں��Ϻ����˺ܾúܾ�......."NOR"\n" ) ;
		call_out("goto_taohua",10,ob) ;
       		return 1;
	} else
		message_vision("�ϴ����������´�����$Nһ�£�ʲô��"
			       "�������㲻Ҫ���ˣ���\n�ϴ���������"
			       "һ�£�����... �������һ�����ӣ���"
			       "�����Կ��ǡ�\n" ,ob);
	ob->set_temp("����", 1);
	return 1;
}

int accept_object(object who, object ob)
{
	object myenv ;
	if (! (int)who->query_temp("����"))
	{
		message_vision("�ϴ���Ц�Ŷ�$N˵���޹�����»��"
			       "�������Լ����Űɣ�\n", who);
		return 0 ;
	}

	if (ob->query("money_id") && ob->value() >= 10000)
	{
		message_vision("�ϴ����$N˵���ã���Ȼ��λ" +
			       RANK_D->query_respect(who) +
			       "��˿������ң�\n����Ҳƴ����"
			       "���ƴ�����������ӱ��ˣ�\n" , who);
		this_player()->delete_temp("����");
		message_vision("�ϴ���һ���֣������������ᴬ��\n", who);
		message_vision("���ᴬ���$N���˴���һ������ê����"
			       "�Ϳ����ˣ����ϴ���ȴû�ϴ�......\n", who);
		myenv = environment(who);
		who->move("/d/taohua/dahai");
		tell_room(myenv, "�ϴ��򿴴����ˣ���������Ľ���Ц�ˣ�ȥ"
				 "�һ����������������ҿɲ��ɡ�\nֻ��ϧ��"
				 "�Ǽ��������Ĵ���Ҫ���ǰ��˸��Ե��ˡ�"
				 "�ٺ٣�������\n") ;
		tell_object(who, BLU "���ں��Ϻ����˺ܾúܾ�......."NOR"\n");
		call_out("goto_taohua", 10, who);
		destruct(ob);
       		return 1;
	} else
		message_vision("�ϴ�����ü��$N˵��������Ҳ̫���˰ɣ�\n", who);

	return 0;
}

void goto_taohua(object ob)
{
   	if (! objectp(ob) || find_object("/d/taohua/dahai") != environment(ob))
		return;

   	tell_object(ob , "������ͣ����һ��С���ߡ������´�����\n");
   	ob->move("/d/taohua/haitan");
}

void unconcious()
{
	::die();
}