//guanjia3.c ������
// Modify By River@SJ

inherit NPC;
#include <ansi.h>

void create()
{
       set_name("������", ({ "mafang guanshi", "guanshi" }) );
       set("gender", "����" );
       set("age", 30);
       set("long","����������ݵ�һ���ܼң�ר������Ĵ�С���£�\n");
       set("combat_exp", 2500);
       set("attitude", "friendly");
       set("inquiry", ([
             "��ɨ��" : "�����������ʵʵ���Ҵ�ɨ����û���ҵ����⣬������ȥ������",
             "��ɨ" : "�����������ʵʵ���Ҵ�ɨ����û���ҵ����⣬������ȥ������",
       ]) );

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
       if(ob->query_temp("job_name") != "��ɨ��") return; 
       if (!( present("sao zhou", ob))){
           command("hmm "+ob->query("id"));
           command("say �㻹û�칤�߰ɣ�ȥ��Ʒ������ʦ��Ҫ��");
           return;
       }
       if(!(ob->query_temp("job_name")!="��ɨ��")){
           command("nod "+ob->query("id"));
           command("say " + RANK_D->query_respect(ob)+"����������ɨ���ɡ�"NOR);
       }
}
