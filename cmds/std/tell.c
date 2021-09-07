#include <ansi.h>
#include <net/dns.h>
inherit F_CLEAN_UP;
#define DEBUG "snowsot"
#ifdef DEBUG
void debug(string x)
{
    object monitor;
    if (!stringp(x) || !stringp(DEBUG))     return;
    monitor=find_player(DEBUG);
    if(monitor && monitor->query("env/debug"))     tell_object(monitor,x+"\n");
}
#else
#define debug(x)
#endif

object find_player(string target)
{
    int i;
    object *str;
    str=users();
    for (i=0;i<sizeof(str);i++)
	if (str[i]->query("id")==target){
	      if (!environment(str[i])) return 0;
	      else
	    return str[i];
	 }
    return 0;
}
int help(object me);
void create() {seteuid(getuid());}
int main(object me, string arg)
{
    string target, msg, mud;
    object obj;
    if( !arg || sscanf(arg, "%s %s", target, msg)!=2 ) return help(me);
    if( userp(me) && !wizardp(me)) {
	if (me->query("chblk_tell")+300>time())
	    return notify_fail("�����ں���˻��,��仰Ҳ˵�����ˡ�\n");
       me->add_temp("tell_msg_cnt", 1);
       if (me->query_temp("tell_msg_cnt")>5)
	    if (time()-me->query_temp("tell_time")<2)
		me->set("chblk_tell",time());
	    else
		me->delete_temp("tell_msg_cnt");
    }

    if( sscanf(target, "%s@%s", target, mud)==2 ) {
	GTELL->send_gtell(mud, target, me, msg);
	write(BOLD "��·ѶϢ���ͳ�������Ҫ�Ժ���ܵõ���Ӧ��"NOR"\n");
	return 1;
    }
    obj = find_player(target);
    if (obj && !userp(me)){
	tell_object(obj, sprintf(BOLD "%sǧ�ﴫ���㣺%s"NOR"\n",
	me->name(1)+"("+me->query("id")+")", msg));
	return  1;
    }
    if (!obj) return notify_fail("û�������....��\n");
    if (!me->visible(obj)) return notify_fail("û�������....��\n");
    if (!interactive(obj)) return notify_fail("û�������....��\n");
    if (obj==me) return notify_fail(PTEXT("������������Ĳ�֪����˵ʲô...\n"));
    debug(sprintf( YEL "%s(%s)����%s(%s)��%s" NOR,me->name(1),me->query("id"),obj->name(1),obj->query("id"), msg));
    if ( member_array("tell", me->query("channels"))==-1)
			me->set("channels", me->query("channels") + ({ "tell" }) );
    write(BOLD+HIG "��ǧ�ﴫ��" + obj->name(1) + "��" + msg + ""NOR"\n");
    if ( (pointerp(obj->query("channels")) && member_array("tell", obj->query("channels"))==-1) && !wizardp(me))
	return notify_fail("��"+obj->name(1)+"�Ѿ���tellƵ���ص���....��\n");
    if (me->id(obj->query("env/no_tell")) )
	return notify_fail("����Ȼ��"+obj->name(1)+"��������������������˵��....��\n");
    tell_object(obj, sprintf(BOLD+HIG "%sǧ�ﴫ���㣺%s"NOR"\n",
	me->name(1)+"("+me->query("id")+")", msg));
    if (query_idle(obj)>120) write(YEL+"����"+obj->name(1)+"�Ѿ�����"+query_idle(obj)/60+"���ӣ������������ϻش���Ӵ��\n"+NOR);
   if (in_edit(obj)) return notify_fail("���ǣ��Է��������ڱ༭������\n");
    obj->set_temp("reply", me->query("id"));
    return 1;
}
string remote_tell(string cname, string from, string mud, string to, string msg)
{
    object ob;
    if( ob = find_player(to) ) {
	if( cname )
	    tell_object(ob, sprintf(PTEXT(BOLD "%s(%s@%s)ǧ�ﴫ���㣺%s"NOR"\n"),
		cname, capitalize(from), mud, msg ));
	else
	    tell_object(ob, sprintf(PTEXT(BOLD "%s@%s ǧ�ﴫ���㣺%s"NOR"\n"),
		capitalize(from), mud, msg ));
	ob->set_temp("reply", from + "@" + mud);
	return ob->name(1);
    } else
	return 0;
}
int help(object me)
{
    write(@HELP
ָ���ʽ��tell <ĳ��> <ѶϢ>
����������ָ��������ط���ʹ����˵����
�������ָ�reply
HELP
    );
    return 1;
}

