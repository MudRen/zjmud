// guanjia5.c �˵ع���
// Modify By River@SJ

inherit NPC;
#include <ansi.h>

void create()
{
       set_name("�˵ع���", ({ "caiyuan guanshi", "guanshi" }) );
       set("gender", "����" );
       set("age", 30);
       set("long", "����������ݵ�һ���ܼң�ר�ܲ˵����С���£�\n");
       set("combat_exp", 2500);
       set("attitude", "friendly");

       set("inquiry", ([
             "����" : "�����������ʵʵ���ҳ����Ӳݣ�û���ҵ����⣬������ȥ������",
       ]));

       setup();
}
void init()
{
       object ob;
       ::init();
       if( interactive(ob = this_player()) && !is_fighting() ) {
              remove_call_out("greeting");
              call_out("greeting", 1, ob);
       }
}
void greeting(object ob)
{
       if( !ob || environment(ob) != environment() ) return;
       if(ob->query_temp("job_name") != "����") return; 
       if(!( present("chu tou", ob))){
           command("hmm "+ob->query("id"));
           command("say �㻹û�칤�߰ɣ�ȥ��Ʒ������ʦ��Ҫ��");
           return;
       }
       if(!(ob->query_temp("job_name")!="����")){
           command("nod "+ob->query("id"));
           command("say "+ RANK_D->query_respect(ob)+ "�����������ݰɡ�"NOR);
       }
}
