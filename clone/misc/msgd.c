#include <ansi.h>

inherit ITEM;
inherit F_SAVE;

#define MSGFILE "/data/msg/msgd.o"

int do_addmsg(string arg);
int do_listmsg(string arg);
int do_delmsg(string arg);

string *msg = ({
			"������fly���help fly��",
			"ƽһָ����������һ���������ͽ�ҩ��ҩЧ��ԭ�����屶��",
			"������ﵽһ�򣬿��Ե�������ask wizard about �������",
			"���������顢��������ҩ�����˾������޵�����50w��������˹�Ǯ������",
			"����mud���������£�����ɾ����",
			"��ҿ�����������Ժ�������̡�ҩ�̺ͳɶ���¥���Թ�����",
			"����mud��ר��Ⱥ�š���589233359��",
	});

static int cnd;

void create()
{
	seteuid(getuid());
	set_weight(900000000);
	set_name("���Ź㲥",({"msgd","msg"}));
	set("channel_id","����ʹ��");
	set("unit", "��");
	set("no_get", 1);
	set("no_drop", 1);
	set("no_give", 1);

	setup();
	if (clonep())
		return;
	CHANNEL_D->do_channel( this_object(), "sys", "����ϵͳ�Ѿ�������\n");	
	call_out("on_time",10);
}

void init()
{
	add_action("do_addmsg","addmsg");
	add_action("do_listmsg","listmsg");
	add_action("do_delmsg","delmsg");
}

int valid_string(string arg)
{
	return 1;
}

int valid_use()
{
	object me=this_player(1);
	
	if (wiz_level(me)<wiz_level("(arch)"))
		return 0;
	return 1;
}
string query_save_file()
{
	return MSGFILE;
}

void on_time()
{
	int i,j;
	
	i=sizeof(msg);
	if (i<=0){
		//CHANNEL_D->do_channel(this_object(),"chat",
		//	"û������\n");
		call_out("on_time",600);
		return;
		}
	
	CHANNEL_D->do_channel(this_object(),"chat",msg[cnd]);
	cnd++;
	if((cnd+1)>=sizeof(msg)) cnd = 0;

	call_out("on_time",600);
}

int do_addmsg(string arg)
{
	object me=this_player(1),ob;
	
	if (!arg||!valid_string(arg))
		return notify_fail("�Ƿ�����Ϣ\n");
	msg += ({arg});
	save();
	tell_object(me,"�����������\n");		
	return 1;
}

int do_listmsg(string arg)
{
	int i;
	
	for (i=0;i<sizeof(msg);i++)
		printf("%4d    :    %s\n",i+1,msg[i]);
	return 1;    
}

int do_delmsg(string arg)
{
	object me=this_player(1),ob;
	int i;
	
	if (sscanf(arg, "%d", i)!=1)
		return notify_fail("��Ҫɾ����һ����Ϣ��\n");
	msg -= ({msg[i-1]});
	save();
	tell_object(me,"����ɾ�����\n");
	return 1;
}
