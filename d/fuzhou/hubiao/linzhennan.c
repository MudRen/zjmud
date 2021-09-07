// linzhennan.c ������

#include <ansi.h>

inherit NPC;
#include "hubiao.h";

int ask_fuwei();
int ask_yuantu();
int ask_pixie();
int ask_tong();

void create()
{
	set_name("������", ({ "lin zhennan", "lin", "zhennan" }));
	set("gender", "����");
	set("age", 45);
	set("long", "�����ǡ������ھ֡�������ͷ���������ϡ�\n");

	set("combat_exp", 800000);
	set("shen_type", 1);
	set("no_get","�����϶�����˵̫���ˡ�\n");

	set("eff_qi", 5000);
	set("max_qi", 5000);
	set("max_neili", 5000);
	set("neili", 5000);
	set("jiali", 100);

	set_skill("force", 190);
	set_skill("sword", 190);
	set_skill("pixie-sword", 190);
	set_skill("unarmed", 190);
	set_skill("dodge", 190);
	set_skill("parry", 190);
	map_skill("parry", "pixie-sword");
	map_skill("sword", "pixie-sword");

	set("inquiry", ([
		"������լ" : "������˵���������Ҵ�ǰ�ڸ���ʱס�ļ�Ժ���Ѿ��ư��ˡ�\n",
		"�����ھ�" : (: ask_fuwei :),
		"Զͼ��" : (: ask_yuantu :),
		"��Զͼ" : "�����ϴ�ŭ��С������ôû��ò��ֱ���������䣡\n",
		"��а����" : (: ask_pixie:),
		"ͭǮ" : (: ask_tong:),
		"����" : (: test_dart :),
	]) );


	set("chat_chance", 2);
	set("chat_msg", ({
		CYN"������˵������������ھ����ⲻ����"NOR"\n",
	}) );

	set_temp("apply/attack", 50);
	set_temp("apply/defense", 50);
	set_temp("apply/damage", 15);

	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/misc/cloth")->wear();
}

int ask_fuwei()
{
 say("��������ҫ��˵�������ּ��������ڣ�һ����������Զͼ�����괳�µ���������\n"
     "�����������ּҼҴ������ն����㺬��������н��յľ��棬��Ϊ����������\n"
     "һָ�Ĵ��ھ֡��������ᵽ�������ھ֡����֣�˭��Ҫ�����Ĵָ��˵һ������\n"
     "�ø����������磡��������������\n");
 this_player()->set_temp("marks/��1", 1);
 return 1;
}

int ask_yuantu()
{
  if ((int)this_player()->query_temp("marks/��1")) {
 say("�����Ͽ�һ���̶���˵����Զͼ�����ҵ��游�������ھ�����һ�ִ���ġ�����\n"
     "�游����ʮ��·��а���������ھ֣������Ǵ��ڵ��޵��֡���ʱ�׵���Ӣ�ۼ�\n"
     "��̫�����磬Ҳ��ȥ�����������յģ�����������������ʦ������������֮ʱ\n"
     "��������а���������˼��С�\n");
 this_player()->set_temp("marks/��2", 1);
 return 1;
  }
  else {
 say("������˵����Զͼ�����ҵ��游��\n");
 return 1;
  }
}

int ask_pixie()
{
  int p1, p2, p3, p4;

  if ((int)this_player()->query("passwd")) {
 say("�����ϲ��õ�˵�����Ҳ��Ƕ������������ҵĽ����������档\n");
  }
  else if ((int)this_player()->query_temp("marks/��2")) {
 say("������һ����˵��������ô֪���ģ��ޣ��Ҹղ�˵¶���ˡ��ˣ����µĹ�������\n"
     "��֪��ϸ����ʵ���������档��\n");
 write("�����϶�һ�٣����Ŷ������˵������ȥ��ǰ�������Ҹ�����");
 p1=random(4)+1;
 p2=random(4)+1;
 p3=random(4)+1;
 p4=random(4)+1;
 this_player()->set("passwd",p1*1000+p2*100+p3*10+p4);
 write(CHINESE_D->chinese_number(p1)+"ǧ"+CHINESE_D->chinese_number(p2)+
       "��"+CHINESE_D->chinese_number(p3)+"ʮ"+CHINESE_D->chinese_number(p4));
 write("��\nͭǮ����һֱδ�����а��ء�\n");
  }
  else {
   message("vision",
   HIY "�����ϲ�Ȼ��ŭ���ȵ�����Ҳ���������ּҵı�а���ף����Ҹ���ƴ�ˣ�\n"
   NOR, environment(), this_object() );
   kill_ob(this_player());
  }
  this_player()->delete_temp("marks/��1");
  this_player()->delete_temp("marks/��2");
  return 1;
}

int ask_tong()
{
  int p, p1, p2, p3, p4;

  if (!(p=(int)this_player()->query("passwd"))) {
 say("������һ����Ц�����ӣ�˵����ô�쵽��һ���˵���ҪǮ��\n");
  }
  else {
 write("�����ϵ���˵������ȥ��ǰ�������Ҹ�����");
 p1=(int)p/1000;
 p2=(int)(p-p1*1000)/100;
 p3=(int)(p-p1*1000-p2*100)/10;
 p4=(int)(p-p1*1000-p2*100-p3*10);
 write(CHINESE_D->chinese_number(p1)+"ǧ"+CHINESE_D->chinese_number(p2)+
       "��"+CHINESE_D->chinese_number(p3)+"ʮ"+CHINESE_D->chinese_number(p4));
 write("��\nͭǮ����һֱδ�����а��ء�\n");
  }

  return 1;
}

