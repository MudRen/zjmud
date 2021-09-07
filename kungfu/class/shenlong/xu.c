// xu.c
#include <ansi.h>
inherit NPC;

int ask_gao();

void create()
{
	set_name("��ѩͤ", ( { "xu xueting", "xu" }) );
	set("title", HIY"������"HIG"����ʹ"NOR);
	set("nickname", HIR "��Ѫ����" NOR);
	set("gender", "����" );
	set("age", 55);
	set("long", "���Ǹ���ʮ����ĸ��ݺ��ӣ���һϮ���£���Ȼͦ����\n");
	
	set("str", 25);
	set("int", 32);
	set("con", 24);
	set("dex", 22);
	
	set("qi", 3900);
	set("max_qi", 3900);
	set("jing", 1900);
	set("max_jing", 1900);
	set("neili", 4400);
	set("max_neili", 4400);
	set("jiali", 100);
	set("combat_exp", 850000);
	set("shen_type", -1);
	
	set_skill("force", 180);
	set_skill("dodge", 170);
	set_skill("unarmed", 180);
	set_skill("parry", 180);
	set_skill("sword", 180);
	set_skill("taoism", 160);
	set_skill("literate", 60);
	set_skill("tiyunzong", 170);
	set_skill("taiji-quan", 180);
	set_skill("taiji-shengong", 180);
	set_skill("taiji-jian", 180);
	set_skill("shedao-qigong", 180);
	set_skill("shenlong-xinfa", 180);
	
	map_skill("force", "taiji-shengong");
	map_skill("dodge", "tiyunzong");
	map_skill("unarmed", "taiji-quan");
	map_skill("parry", "taiji-jian");
	map_skill("sword", "taiji-jian");
	
	create_family("������", 0, "����");

	set("inquiry", ([
		"�ٻ����߸�" : (: ask_gao :),
		"������" : "һ�������벻���������̵�(join shenlongjiao).\n",
		"�鰲ͨ" : "����Ƣ������,Ҫ�������Ĳźá�\n",
		"����"   : "����Ƣ������,Ҫ�������Ĳźá�\n",
		"���"   : "һ�������벻���������̵�(join shenlongjiao).\n",
		"�ں�"   : "���겻�ϣ������ɸ����������룡������ʥ��\n",
	]));
	
	set("chat_chance", 1);
	set("chat_msg", ({
		"��ѩͤ��Ȼһ���Դ���˵�����ˣ������ðٻ����߸࣡\n",
		"��ѩͤŭ��������ټ��һ�������̣�������һ�����������ˣ�\n",
		"��ѩͤ̾������˵����������ɱ�˺鰲ͨ��˭Ҳ��ˡ�\n",
	}) );
	setup();
	carry_object("/d/city/obj/duanjian")->wield();
}

int ask_gao()
{
	say(
	"\n��ѩͤ��������˵������Ǳ��̽��ﰡ����һ����Ѫ������Ũ�㣬\n"
	"����ס�������ߵ��ϣ����˶��������ۻƾƣ��Աܶ��ߣ��������\n"
	"һ�����ۻƾƣ���ʹ�˽���������ܶ��������ˣ�����ôҲ֪����\n"
		);
	return 1;
}

int accept_object(object who, object ob)
{
	object obn;

	if( !who || environment(who) != environment() ) return 0;
	if ( !objectp(ob) ) return 0;
	if ( !present(ob, who) ) return notify_fail("��û�����������\n");

	if (is_busy())
	{
		command("say ����������ʲô��");
		return 0;
	}

	if (  (string)ob->query("id") != "fushe dan"
		&& (string)ob->query("id") != "baixiang hua" )
		    return notify_fail("��ѩͤҡͷ�������ɱ���˺鰲ͨ������ʲôҲû�ð�������\n");

	if ( (string)ob->query("id") == "fushe dan" )
		{
		  if(query_temp("baixianghua"))
		  {
		  message_vision("\n��ѩͤ���Ǹ��ߵ�����ϲ�������ߵ����㻨�����ˣ��ٻ����߸������ˣ�\n",who);
		  obn=new("/d/shenlong/obj/baihua");
		  obn->move(who);
		  delete_temp("fushedan");
		  delete_temp("baixianghua");
		  destruct(ob);
		  return 1;
		  }
		  else	
		  {
		  if(query_temp("fushedan"))
		  {
    			   message_vision("\n��ѩͤ���Ǹ��ߵ�����$Nҡͷ�������ߵ������ˣ��Ͳ���㻨�ˡ�\n",who);
			   return 0;
		  }
		  else	  
		  {
		  message("vision","��ѩͤ�������ߵ�����ϲ�������˸��ߵ���ֻ����㻨�ˡ�\n",environment(who));
		  set_temp("fushedan",1);
		  destruct(ob);
		  return 1;
		  }
		}
	}
	if ( (string)ob->query("id") == "baixiang hua")
		{
		  if(query_temp("fushedan"))
		  {
		  message_vision("\n��ѩͤ���ǰ��㻨����ϲ�������ߵ����㻨�����ˣ��ٻ����߸������ˣ�\n",who);
		  obn=new("/d/shenlong/obj/baihua");
		  obn->move(who);
		  delete_temp("fushedan");
		  delete_temp("baixianghua");
		  destruct(ob);
		  return 1;		 
		  } 		
		  else	
		  {	
		  if(query_temp("baixianghua"))
		  {
			   message_vision("\n��ѩͤ���ǰ��㻨����$Nҡͷ�������㻨�����ˣ��Ͳ�ߵ��ˡ�\n",who);
			   return 0;
		  }
		  else	  
		  {
		  message("vision","��ѩͤ�������㻨����ϲ�������˰��㻨��ֻ��ߵ��ˡ�\n",environment(who));
		  set_temp("baixianghua",1);
		  destruct(ob);
		  return 1;
		  }
		 }	
	}
}

void attempt_apprentice(object ob)
{
	command("say �Ҳ���ͽ�����ҽ���ȥ�ɣ� ");
	return;
}

