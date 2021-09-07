// mao18.c éʮ�� 
	
	
#include <ansi.h> 
	
inherit NPC; 
	
void create() 
{ 
	set_name("éʮ��", ({ "mao shiba", "mao", "shiba" })); 
	set("gender", "����"); 
	set("age", 30); 
	set("str", 25); 
	set("dex", 16); 
	set("long", "��������Ҳݣ�����Ѫ�ۣ��������ܹ����ص��ˣ����Կ��ü�\n" 
	    "��������Ѫ��δ�ɡ�����˫Ŀ������ȴ������˵���������硣\n"); 
	set("combat_exp", 35000); 
	set("shen_type", 1); 
	set("score", 4000); 
	set("attitude", "peaceful"); 
       
	set_skill("unarmed", 50); 
	set_skill("force", 60); 
	set_skill("blade", 80); 
	set_skill("dodge", 50); 
	set_skill("parry", 50); 
       
	set_skill("wuhu-duanmendao", 70); 
       
	set_temp("apply/attack", 30); 
	set_temp("apply/defense", 30); 
	set_temp("apply/armor", 5); 
	set_temp("apply/damage", 10); 
       
	map_skill("blade", "wuhu-duanmendao"); 
       
	set("neili", 200);  
	set("max_neili", 200); 
	set("jiali", 20); 
	set("inquiry", ([ 
		"ʷ��" : "ɱ��ʷ���������������߽���������\n", 
		"����" : "������������ͷ��������", 
	])); 
       
	set("chat_chance", 2); 
	set("chat_msg", ({ 
		"\néʮ��˵��: �����̵ģ��ҾͲ����������������,\n" 
		"����Ҫ�ϱ���ȥ����һ����" , 
		"\néʮ��̾��: �������廢���ŵ����Ը����ɿ��Ǵ´�����,ֻ��֪�Ը������в��С�\n", 
		"\néʮ��˵��: ������������Ҫ�������ߴ��кô���...\n", 
		"\néʮ��˵��: �����̵ģ�˭����ɱ��ʷ�ɣ��ֵ���лл���ˣ�\n", 
		"\néʮ��˵��: ������˵�������������޵�һ��ʿ�������,\n" 
		"������˵�������µ�һ��ʿ���ҿɲ�������Ҫ�ϱ���ȥ�����Ȼ��Ȼ���\n" , 
		"\néʮ������˵�����������ԣ���Ϊ�˲�ʶ�½��ϣ��ͳ�Ӣ��Ҳ��Ȼ����\n", 
		(: random_move :) 
	}) ); 
	setup(); 
	carry_object("/d/city/obj/gangdao")->wield(); 
	carry_object("/clone/misc/cloth")->wear(); 
} 
       
void init() 
{	
	object ob;  
       
	::init(); 
	if (interactive(ob = this_player())) 
	{ 
		remove_call_out("greeting"); 
		call_out("greeting", 1, ob); 
	} 
} 
       
void greeting(object ob) 
{ 
	if (! ob || environment(ob) != environment()) return; 
	message_vision("$N���ֵ����ֵ����ϲ����㣬�������������ˡ�\n", this_object()); 
} 
       
void die() 
{ 
	say("éʮ�˹�����Ц������Τ�ֵܵĸ����Ҽ����˳½����ܶ����������޺�����\n"); 
	::die(); 
} 
       
int accept_object(object me, object ob) 
{ 
	if (ob->query("id") == "heilong bian") 
	{ 
		if (! me->query_temp("can_learn/mao18/wuhu-duanmendao")) 
		{ 
			message_vision("$Nϲ��������л��λ" + 
				       RANK_D->query_respect(me) + 
				       "�������������廢���ŵ������������Ȥ����\n", 
				       this_object()); 
			me->set_temp("can_learn/mao18/wuhu-duanmendao", 1); 
		} 
		me->set_temp("can_learn/mao18/wuhu-duanmendao", 1); 
       
		if (me->query("weiwang") < 200)
		{
			me->add("weiwang", 10); 
			message_vision(HIC "$N�Ľ�����������ˣ�"NOR"\n", this_player()); 
		}
		destruct(ob); 
		return -1; 
	} 
      
	command("say ���ֶ������Ҫ��������"); 
	return 0; 
} 
      
int recognize_apprentice(object me, string skill) 
{ 
	if (! me->query_temp("can_learn/mao18/wuhu-duanmendao"))
	{
		command("say �����˰�.... �ٺ٣��ҵÿ��ǿ��ǡ�");
		return -1;
	}
      
	if (skill != "wuhu-duanmendao") 
		return 0; 
      
	return 1; 
} 
      
