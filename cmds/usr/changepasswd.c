//cpasswd.c by XiaoYao
// Modify by snowman@SJ 01/05/1999.

#include <ansi.h>
#include <login.h>;

int main(object me, string arg)
{
	object ob,link_ob;
	string id,password;
	
	seteuid(ROOT_UID); // add by Yuj@SJ 1999-6-2
	if( me != this_player(1) ) return 0;
		
	if(!arg||sscanf(arg,"%s %s",id,password)!=2)
		return notify_fail("��ʽ�� changepasswd �Լ���ID ������\n");

	ob = LOGIN_D->find_body(id);
	if(!ob) return notify_fail("��ֻ���޸��Լ������롣\n");
	
	link_ob=ob->query_temp("link_ob");
	if(link_ob && me->query("id")==ob->query("id")) {
		link_ob->set("password",crypt(password,"$1$ShuJian"));
		link_ob->save();
		write("�����Ϸ�����Ѿ�����Ϊ��"+password+"\n");
		write(HIR"��ͬ���޸���Ŀͻ������룬�����㽫�޷���½��"NOR"\n");
		write(HIY+ZJSIZE(22)"�������ѿͻ�������ĳɣ�"+password+"
�������ѿͻ�������ĳɣ�"+password+"
�������ѿͻ�������ĳɣ�"+password+"
��Ҫ������˵���飬
�������µ�¼ʱ��Ҫѡ�� �ϴε�¼"NOR"\n");
		log_file("changepw", sprintf("%s��%s(%s)��%s(%s)�������Ϊ %s\n", ctime(time()), me->query("name"), me->query("id"),
				 ob->query("name"), ob->query("id"), password));
		return 1;
	}
	else
		return notify_fail("��ֻ���޸��Լ������롣\n");
	return 1;
}


int help(object me)
{
	write(@HELP
ָ���ʽ : changepasswd ID ������

���ָ������޸��Լ�����Ϸ���룬��Ϸ���޸�������󣬻������ͻ��˵��û����İѾ�����ĳ������롣
����ر��ֿͻ��˺���Ϸ�����໥һ�£������޷�������½��

HELP
    );
    return 1;
}
